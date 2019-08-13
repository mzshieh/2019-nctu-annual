import java.io.File
import java.math.BigDecimal
import java.math.BigInteger
import kotlin.system.exitProcess

private fun nextLine() = readLine()!!
private fun nextToks() = nextLine().split(" ").filter{it != ""}
private fun nextInts() = nextToks().map{it.toInt()}
private fun nextBigDecs() = nextToks().map{BigDecimal(it)}
private fun nextBigs() = nextToks().filter{it.length<=100}.map{BigInteger(it)}

fun verdict(v: Boolean, msg: String = "Should be EOF") {
    if (!v) throw Exception(msg)
}

fun verify(input: List<String>, ans: List<String>) {
    val n = input[0].toInt()
    var out: MutableSet<Pair<BigInteger,BigInteger>> = mutableSetOf()
    for (rnd in 1..n) {
        var cand = nextBigs()
        verdict(cand.size == 3, "Not three numbers: $cand")
        cand = cand.filter{it > BigInteger.ZERO}
        verdict(cand.size == 3, "Negative numbers")
        val (a, b, c) = cand
        verdict(a < b && b < c, "Not in ascending order: $a $b $c")
        verdict(a.gcd(b).gcd(c) == BigInteger.ONE, "Not coprime: $a $b $c")
        verdict(a*a + b*b == c*c, "Not Pythaorean")
        verdict(!out.contains(Pair(a,b)), "Repeated: $a $b $c")
        out.add(Pair(a,b))
    }
    verdict(readLine() == null)
}

// usage: judge_in judge_ans feedback_dir [options] < team_out

fun main(args: Array<String>) {
    try{
        verify(File(args[0]).readLines(), File(args[1]).readLines())
    } catch (e: Exception) {
        println("Wrong Answer")
        println("$e")
        exitProcess(43)
    }
    println("Correct")
    exitProcess(42)
}
