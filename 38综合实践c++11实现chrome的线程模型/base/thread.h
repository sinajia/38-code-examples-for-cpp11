_Pragma("once")

#include <thread>
#include <chrono>
#include "./message_loop.h"
#include "./event.h"

namespace base {

    class Thread {
    public:

        struct Options {
            Options();
            Options(MessageLoop::Type type, unsigned int size);

            unsigned int stack_size_;
            MessageLoop::Type message_loop_type_;
        };

        struct StartupData {
            const Options& options_;
            WaitableEvent event_;

            explicit StartupData(const Options& options) :
                options_(options), event_(false, false) {}
        };

        class ScopedCOMInitializer {
        public:
            ScopedCOMInitializer();
            ~ScopedCOMInitializer();
        };

        explicit Thread();
        virtual ~Thread();

        void Init();
        bool StartWithOptions(const Options& options);
        void Stop();

        MessageLoop* message_loop() const { return message_loop_.get(); }
        std::thread::id thread_id() const { return thread_.get_id(); }
        bool IsRunning() const { return  running_; }

        virtual void ThreadMain();
        //static
        static bool CreateThreadInternal(Thread * ptr);

        Thread(const Thread&) = delete;
        Thread(Thread&&) = delete;
        void operator=(const Thread&) = delete;
        void operator=(Thread&&) = delete;

    protected:
        virtual void CleanUp();

    private:
        void Run(MessageLoop* message_loop);

        std::unique_ptr<MessageLoop> message_loop_;

        StartupData* startup_data_;

        // Whether we successfully started the thread.
        bool started_;

        // If true, we're in the middle of stopping, and shouldn't access
        // |message_loop_|. It may non-NULL and invalid.
        bool stopping_;

        // True while inside of Run().
        bool running_;

        std::thread thread_;

    };


} // end base
