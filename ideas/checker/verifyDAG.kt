import kotlin.system.exitProcess
import java.io.File
import java.math.BigInteger
import java.math.BigDecimal

fun testIf(pred: Boolean, msg: String) {
    if (!pred) throw Exception(msg)
}

fun verify(input: List<String>, answer: List<String>) {
    println("${input.size} ${answer.size}")
	val (sn, sk, sa) = input[0].split(" ").filter{it.length>0}
	val n = sn.toInt()
	val k = sk.toInt()
    val a = sa.toBigDecimal().setScale(10000)
	val adj = (1 until n).map{readLine()!!.split(" ").filter{it.length>0}.map{it.toInt()-1}}
	adj.forEach{println("$it")}
	var dp = Array<BigInteger>(n){BigInteger.ZERO}
	dp[0] = BigInteger.ONE
	for (i in 0 until n-1) {
		for (j in adj[i]) dp[j] += dp[i]
	}
	println(dp[n-1])
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
