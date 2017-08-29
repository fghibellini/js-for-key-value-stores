
#include <stdio.h>
#include <chrono>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include "libplatform/libplatform.h"
#include "v8.h"

using namespace v8;

#define CTX_COUNT 500

int main(int argc, char* argv[]) {

    // Initialize V8.
    V8::InitializeICUDefaultLocation(argv[0]);
    V8::InitializeExternalStartupData(argv[0]);
    Platform* platform = platform::CreateDefaultPlatform();
    V8::InitializePlatform(platform);
    V8::Initialize();

    // Create a new Isolate and make it the current one.
    Isolate::CreateParams create_params;
    create_params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    Isolate* isolate = Isolate::New(create_params);

    {
        Isolate::Scope isolate_scope(isolate);
        // Create a stack-allocated handle scope.
        HandleScope handle_scope(isolate);

        // CONTEXT CREATION
        std::chrono::time_point<std::chrono::high_resolution_clock> ctx_creation_start = std::chrono::high_resolution_clock::now();
        std::vector<Local<Context>> contexts;
        for (int i = 0; i < CTX_COUNT; i++)
        {
            // Create a new context.
            contexts.push_back(Context::New(isolate));
        }
        std::chrono::time_point<std::chrono::high_resolution_clock> ctx_creation_end = std::chrono::high_resolution_clock::now();
        printf("Context creation: %ld µs\n", std::chrono::duration_cast<std::chrono::microseconds>(ctx_creation_end - ctx_creation_start).count() / CTX_COUNT);

        // JS COMPILATION
        std::chrono::time_point<std::chrono::high_resolution_clock> js_compilation_start = std::chrono::high_resolution_clock::now();
        std::vector<Local<Script>> fns; 
        for (int i = 0; i < CTX_COUNT; i++)
        {
            auto &context = contexts[i];

            // Enter the context for compiling and running the hello world script.
            Context::Scope context_scope(context);

            // Create a string containing the JavaScript source code.
            Local<String> source = String::NewFromUtf8(isolate, "(function() {})()", NewStringType::kNormal).ToLocalChecked();
            // Compile the source code.
            fns.push_back(Script::Compile(context, source).ToLocalChecked());

        }
        std::chrono::time_point<std::chrono::high_resolution_clock> js_compilation_end = std::chrono::high_resolution_clock::now();
        printf("JS compilation: %ld µs\n", std::chrono::duration_cast<std::chrono::microseconds>(js_compilation_end - js_compilation_start).count() / CTX_COUNT);

        // JS CALL
        const int CALL_COUNT = 10000;
        {
            auto &context = contexts[0];
            auto &script = fns[0];
            // Enter the context for compiling and running the hello world script.
            Context::Scope context_scope(context);

            std::chrono::time_point<std::chrono::high_resolution_clock> js_call_start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < CALL_COUNT; i++)
            {

                // Run the script to get the result.
                script->Run(context).ToLocalChecked();
            }
            std::chrono::time_point<std::chrono::high_resolution_clock> js_call_end = std::chrono::high_resolution_clock::now();
            printf("JS call: %ld ns\n", std::chrono::duration_cast<std::chrono::nanoseconds>(js_call_end - js_call_start).count() / CALL_COUNT);
        }

        // CONTEXT SWITCH
        std::chrono::time_point<std::chrono::high_resolution_clock> ctx_switch_start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < CTX_COUNT; i++)
        {
            auto &context = contexts[i];
            auto &script = fns[i];

            // Enter the context for compiling and running the hello world script.
            Context::Scope context_scope(context);

            // Run the script to get the result.
            script->Run(context).ToLocalChecked();
        }
        std::chrono::time_point<std::chrono::high_resolution_clock> ctx_switch_end = std::chrono::high_resolution_clock::now();
        printf("Calls in different context: %ld µs\n", std::chrono::duration_cast<std::chrono::microseconds>(ctx_switch_end - ctx_switch_start).count() / CTX_COUNT);
    }

    // Dispose the isolate and tear down V8.
    isolate->Dispose();
    V8::Dispose();
    V8::ShutdownPlatform();
    delete platform;
    delete create_params.array_buffer_allocator;
    return 0;
}
