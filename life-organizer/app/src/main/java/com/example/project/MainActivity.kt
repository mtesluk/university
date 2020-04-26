package com.example.project

import android.content.Context
import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.Toast
import kotlinx.android.synthetic.main.activity_main.*
import java.io.IOException
import okhttp3.*
import android.widget.ArrayAdapter
import com.allyants.notifyme.NotifyMe
import com.wdullaer.materialdatetimepicker.time.TimePickerDialog
import java.util.*


class MainActivity : AppCompatActivity()  {
    private val isDevelop: Int = 1 // on Android Studio emulator date is counted 1 month to past
    private var context: Context? = null
    private var db: DbHandler? = null
    private val url: String = "http://quotes.rest/qod.json?category=funny"
    private var quoteData: MutableMap<String, String> = mutableMapOf()
    private var calendar: Calendar? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        context = applicationContext
        db = DbHandler(this, "determination")
        calendar = Calendar.getInstance()

        setStartTime()
        setEndTime()
        setSaveButtonListener()
        setListButtonListener()
        setStatsButtonListener()
        setSelect()
        fetchQuote()
    }

    private fun setStartTime() {
        startTime.setOnClickListener {
            var time = TimePickerDialog.newInstance(
                { _, hour, minute, _ ->
                    val time: String = "$hour:$minute"
                    startTime.setText(Util.handleTime(time))
                },
                calendar!!.get(Calendar.HOUR_OF_DAY),
                0,
                calendar!!.get(Calendar.SECOND),
                true
            )

            time.show(fragmentManager, "Start Time Picker")
        }
    }

    private fun setEndTime() {
        endTime.setOnClickListener {
            var time = TimePickerDialog.newInstance(
                { _, hour, minute, _ ->
                    val time: String = "$hour:$minute"
                    endTime.setText(Util.handleTime(time))
                },
                calendar!!.get(Calendar.HOUR_OF_DAY),
                0,
                calendar!!.get(Calendar.SECOND),
                true
            )

            time.show(fragmentManager, "Start Time Picker")
        }
    }

    private fun setSaveButtonListener() = setButton.setOnClickListener {
        val selectedItem: String = selectDay.selectedItem.toString()
        val selectedDate: String = Util.handleDate(selectedItem)
        saveData(selectedDate)
        if (startTime.text.isNotEmpty() and endTime.text.isNotEmpty()) {
            setNotification(selectedDate)
        }
        clearElements()
        showToastMessage("Element saved...")
    }

    private fun setListButtonListener() = listButton.setOnClickListener {
        val intent = Intent(this,
            ListActivity::class.java)

        startActivityForResult(intent, 101)
    }

    private fun setStatsButtonListener() = statsButton.setOnClickListener {
        val intent = Intent(this,
            StatsActivity::class.java)

        startActivityForResult(intent, 102)
    }

    private fun saveData(selectedDate: String) {
        val startData: String = startTime.text.toString()
        val endData: String = endTime.text.toString()
        db!!.addData(startData,
            endData,
            purposeEdit.text.toString(),
            selectedDate,
            0
            )
    }

    private fun setNotification(selectedDate: String) {
        val dateList = selectedDate.split("-")
        val startTimeList = startTime.text.split(":")
        val endTimeList = endTime.text.split(":")

        calendar!!.set(dateList[0].toInt(), dateList[1].toInt()-isDevelop, dateList[2].toInt(), startTimeList[0].toInt(), startTimeList[1].toInt(), 1)

        var notifyMeStart: NotifyMe.Builder  = NotifyMe.Builder(context)
            .title("Daily reminder - STARTED")
            .content(purposeEdit.text.toString())
            .color(250,0,0, 255)
            .led_color(255,255,255,255)
            .large_icon(R.mipmap.ic_launcher)
            .time(calendar)

        notifyMeStart.build()

        val intent: Intent = Intent(this,
            ConfirmActivity::class.java)

        val budle: Bundle = Bundle()
        budle.putString("text", purposeEdit.text.toString())
        intent.putExtras(budle)

        calendar!!.set(dateList[0].toInt(), dateList[1].toInt()-isDevelop, dateList[2].toInt(), endTimeList[0].toInt(), endTimeList[1].toInt(), 1)
        var notifyMeEnd: NotifyMe.Builder  = NotifyMe.Builder(context)
            .title("Daily reminder - FINISHED")
            .content(purposeEdit.text.toString())
            .color(250,0,0, 255)
            .led_color(255,255,255,255)
            .large_icon(R.mipmap.ic_launcher_round)
            .time(calendar)
            .addAction(intent, "Confirm")

        notifyMeEnd.build()

    }

    private fun clearElements() {
        startTime.setText("")
        endTime.setText("")
        purposeEdit.setText("")
    }

    private fun fetchQuote() {
        val client = OkHttpClient()
        val req = Request.Builder().url(url).build()
        client.newCall(req).enqueue(object : Callback {
            override fun onResponse(call: Call, response: Response) {
                val body = response.body()?.string()
                val serializer = Serializer(body)
                if (serializer.valid) {
                    quoteData = serializer.data

                    runOnUiThread {
                        progressBar.visibility = View.INVISIBLE
                        quoteText.text = quoteData.get("quote")
                        authorText.text = quoteData.get("author")
                    }
                } else {
                    Log.e("WARNING", "Connection limit rate...")
                    showToastMessage("Connection limit rate...")
                    progressBar.visibility = View.INVISIBLE
                }
            }

            override fun onFailure(call: Call, e: IOException) {
                runOnUiThread {
                    Log.e("ERROR", "No internet connection...")
                    Toast.makeText(context, "No connection...", Toast.LENGTH_LONG).show()
                    progressBar.visibility = View.INVISIBLE
                }
            }
        })
    }

    private fun setSelect() {
        ArrayAdapter.createFromResource(this,
            R.array.planets_array,
            android.R.layout.simple_spinner_item).also { adapter ->
            adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
            selectDay.adapter = adapter
        }
    }

    private fun showToastMessage(text: String) {
        runOnUiThread {
            val toast = Toast.makeText(context, text, Toast.LENGTH_LONG)
            val view = toast.view
            view.setBackgroundResource(R.color.background_material_dark)
            toast.setGravity(Config.TOAST_GRAVITY, 0 ,Config.TOAST_Y_OFFSET)
            toast.show()
        }
    }
}
