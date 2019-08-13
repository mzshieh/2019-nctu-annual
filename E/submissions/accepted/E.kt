import java.math.BigInteger

fun main() {
    val n = readLine()!!.toInt()
    for (i in 1..n) {
        val a = BigInteger("${2*i+1}")
        val b = (a*a-BigInteger.ONE)/BigInteger.TWO
        val c = b+BigInteger.ONE
        println("$a $b $c")
    }
}
