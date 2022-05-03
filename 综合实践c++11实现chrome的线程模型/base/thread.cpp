#include "./thread.h"
#include <Windows.h>  /*  TODO->unix不需要，用条件编译   */

namespace base {

    Thread::Options::Options()
        : message_loop_type_(MessageLoop::TYPE_DEFAULT), stack_size_(0) {
    }

    Thread::Options::Options(MessageLoop::Type type, unsigned int size)
        : message_loop_type_(type), stack_size_(size) {
    }

    Thread::Thread() : started_(false),
        stopping_(false),
        running_(false),
        startup_data_(nullptr) {
        Init();
    }

    /*  TODO->unix不需要，用条件编译   */
    Thread::ScopedCOMInitializer::ScopedCOMInitializer() {
        ::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    }

    Thread::ScopedCOMInitializer::~ScopedCOMInitializer() {
        ::CoUninitialize();
    }

    Thread::~Thread() {
        Stop();
    }

    void Thread::Init() {
        message_loop_.reset(nullptr);
    }

    bool Thread::StartWithOptions(const Options& options) {
        StartupData startup_data(options);
        startup_data_ = &startup_data;
        std::thread thread(CreateThreadInternal, this);
        thread_ = std::move(thread);
        startup_data.event_.Wait();
        startup_data_ = nullptr;
        started_ = true;
        return true;
    }

    void Thread::Stop() {
        if (!started_)
            return;

        if (stopping_ || !message_loop_.get())
            return;

        stopping_ = true;

        message_loop_->Quit();

        thread_.join();

        started_ = false;
        stopping_ = false;
    }

    void Thread::ThreadMain() {
        auto com_initializer = std::make_unique<ScopedCOMInitializer>();

        message_loop_.reset(new MessageLoop(startup_data_->options_.message_loop_type_));
        
        running_ = true;

        startup_data_->event_.Signal();

        Run(message_loop_.get());

        running_ = false;
        // Let the thread do extra cleanup.
        CleanUp();
    }

    // static
    bool Thread::CreateThreadInternal(Thread * ptr) {
        ptr->ThreadMain();
        return true;
    }

    void Thread::CleanUp() {
        message_loop_.reset(nullptr);
    }

    void Thread::Run(MessageLoop* message_loop) {
        message_loop->Run();
    }

} // end base
