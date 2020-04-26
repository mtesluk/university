package com.example.project

import java.time.LocalDate
import java.time.LocalTime

class Util {
    companion object {
        fun handleTime(time: String): String {
            if (time.length > 0) {
                var firstPart = time.split(":")[0]
                var secondPart = time.split(":")[1]

                if (firstPart.length == 1) firstPart = "0$firstPart"
                if (secondPart.length == 1) secondPart = "0$secondPart"

                return "$firstPart:$secondPart"
            } else {
                return ""
            }
        }

        fun handleTag(done: Int, startTime: String, endTime: String, today: Boolean): String {
            var tag: String = ""
            if (startTime.isEmpty()) tag = "IDEA"
            else if (LocalTime.now().isAfter(LocalTime.parse(startTime)) &&
                LocalTime.now().isBefore(LocalTime.parse(endTime)) &&
                today) {
                tag = "ONGOING"
            }
            else if (done == 1) tag = "DONE"
            else if (done == 0) tag = "PLAN"
            return tag
        }

        fun handleDate(day: String): String {
            return if (day == "Today") LocalDate.now().toString() else  LocalDate.now().plusDays(1).toString()
        }
    }
}