import kotlinx.cinterop.*
import libchatllm.*

@OptIn(kotlinx.cinterop.ExperimentalForeignApi::class)
fun chatllm_print(userData: COpaquePointer?, printType: UInt, utf8Str: CPointer<ByteVar>?) {
    when (printType) {
        PRINT_CHAT_CHUNK -> print(utf8Str?.toKString())
        else -> println(utf8Str?.toKString())
    }
}

@OptIn(kotlinx.cinterop.ExperimentalForeignApi::class)
fun chatllm_end(userData: COpaquePointer?) {
    println()
}

@OptIn(kotlinx.cinterop.ExperimentalForeignApi::class)
fun main(args: Array<String>) {
    val chat = chatllm_create() ?: error("Failed to create chatllm object")

    args.forEach { arg ->
        chatllm_append_param(chat, arg)
    }

    val printProc = staticCFunction(::chatllm_print)
    val endProc = staticCFunction(::chatllm_end)

    val r = chatllm_start(chat, printProc, endProc, null)
    if (r != 0) {
        println(">>> chatllm_start error: $r")
        return
    }

    while (true) {
        print("You  > ")
        val input = readlnOrNull()
        if (input.isNullOrBlank()) continue

        print("A.I. > ")
        val r = chatllm_user_input(chat, input)
        if (r != 0) {
            println(">>> chatllm_user_input error: $r")
            break
        }
    }
}