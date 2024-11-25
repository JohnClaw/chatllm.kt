# chatllm.kt
kotlin api wrapper for llm-inference chatllm.cpp

All credits go to original repo: https://github.com/foldl/chatllm.cpp and Qwen 2.5 32b Coder Instruct which made 99% of work. I only guided it with prompts.

Generation of C interop bindings:

cinterop -def libchatllm.def -o C:\ktnt\bin\libchatllm_interop

Compilation of executable:

kotlinc-native main.kt -library C:\ktnt\bin\libchatllm_interop.klib -linker-options -L. -linker-options -llibchatllm -o main
