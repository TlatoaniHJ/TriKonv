fun main() {
    searchHiKonv(9)
    searchHiKonvSigned(4)
    searchTriKonv(2)
}

const val TOTAL_BITS = 64

fun searchHiKonv(diff: Int) {
    var best = Pair(0, 0)
    var bestQuantity = 1000.0
    for (a in 1 until 16) {
        for (b in 1 until 16) {
            val bitsPer = TOTAL_BITS / (a + b - 1)
            val valuesPer = 1 + (diff * a)
            val quantity = (100.0 * (((2 * b) + 4).toDouble() / (a * b).toDouble())) + (((2 * (a - 1)) - 1).toDouble() / a.toDouble())
            if (1 shl bitsPer >= valuesPer) {
                if (quantity < bestQuantity) {
                    best = Pair(a, b)
                    bestQuantity = quantity
                }
            }
        }
    }
    println("HiKonv unsigned: for difference $diff | best = $best, quantity = $bestQuantity")
}

fun searchHiKonvSigned(limit: Int) {
    var best = Pair(0, 0)
    var bestQuantity = 1000.0
    for (a in 1 until 16) {
        for (b in 1 until 16) {
            val bitsPer = TOTAL_BITS / (a + b - 1)
            val maxPositive = limit * a
            val quantity = (100.0 * (((8 * b) + 1).toDouble() / (a * b).toDouble())) + (((8 * (a - 1)) - 5).toDouble() / a.toDouble())
            if (1 shl (bitsPer - 1) > maxPositive) {
                if (quantity < bestQuantity) {
                    best = Pair(a, b)
                    bestQuantity = quantity
                }

            }
        }
    }
    println("HiKonv signed: for limit $limit | best = $best, quantity = $bestQuantity")
}

fun searchTriKonv(diff: Int) {
    var best = Pair(0, 0)
    var bestQuantity = 1000.0
    for (a in 1 until 16) {
        for (b in 1 until 16) {
            val bitsPer = TOTAL_BITS / (a + b - 1)
            val valuesPer = 1 + (diff * a)
            val quantity = (100.0 * (((3 * b) + 5).toDouble() / (a * b).toDouble())) + (((3 * (a - 1)) - 1).toDouble() / a.toDouble())
            if (1 shl bitsPer >= valuesPer) {
                if (quantity < bestQuantity) {
                    best = Pair(a, b)
                    bestQuantity = quantity
                }
            }
        }
    }
    println("TriKonv: for difference $diff | best = $best, quantity = $bestQuantity")
}