import kotlin.system.exitProcess
import java.io.File

fun testIf(pred: Boolean, msg: String) {
    if (!pred) throw Exception(msg)
}

fun verify(input: List<String>, answer: List<String>) {
    println("${input.size} ${answer.size}")
}

fun main(args: Array<String>) {
    try{
        verify(File(args[0]).readLines(), File(args[1]).readLines())
    } catch (e: Exception) {
        println(e)
		println("Wrong Answer")
        exitProcess(43)
    }
	println("Correct")
    exitProcess(42)
}
