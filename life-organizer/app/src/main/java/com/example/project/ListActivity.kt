package com.example.project

import android.content.Context
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.TextView
import android.widget.Toast
import kotlinx.android.synthetic.main.activity_list.*
import java.time.LocalDate

class ListActivity : AppCompatActivity() {
    private var db: DbHandler? = null
    private var context: Context? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_list)
        context = applicationContext
        db = DbHandler(this, "determination")

        getTodayData()
        getTomorrowData()

        setBackButtonListener()
        setClearButtonTodayListener()
        setClearButtonTomorrowListener()
    }

    override fun onResume() {
        super.onResume()
        getTodayData()
        getTomorrowData()
    }

    private fun getTodayData() {
        layoutTodayText.removeAllViews()
        layoutTodayStatus.removeAllViews()
        layoutTodayTime.removeAllViews()
        var dataToday = db!!.getDataBy("date", LocalDate.now().toString())

        while(dataToday.moveToNext()) {
            val startTime: String = Util.handleTime(dataToday.getString(dataToday.getColumnIndex("start_time")))
            val endTime: String = Util.handleTime(dataToday.getString(dataToday.getColumnIndex("end_time")))
            val text = dataToday.getString(dataToday.getColumnIndex("text"))
            var done: String = Util.handleTag(dataToday.getInt(dataToday.getColumnIndex("done")), startTime, endTime, true)
            val textViewText = TextView(context)
            val textViewStatus = TextView(context)
            val textViewTime = TextView(context)
            textViewText.text = text
            textViewStatus.text = done
            textViewTime.text = if (!startTime.isEmpty()) "$startTime - $endTime" else ""
            layoutTodayText.addView(textViewText)
            layoutTodayStatus.addView(textViewStatus)
            layoutTodayTime.addView(textViewTime)
        }
    }

    private fun getTomorrowData() {
        layoutTomorrowText.removeAllViews()
        layoutTomorrowStatus.removeAllViews()
        layoutTomorrowTime.removeAllViews()
        var dataTomorrow = db!!.getDataBy("date", LocalDate.now().plusDays(1).toString())

        while(dataTomorrow.moveToNext()) {
            val startTime = Util.handleTime(dataTomorrow.getString(dataTomorrow.getColumnIndex("start_time")))
            val endTime = Util.handleTime(dataTomorrow.getString(dataTomorrow.getColumnIndex("end_time")))
            val text = dataTomorrow.getString(dataTomorrow.getColumnIndex("text"))
            var done: String = Util.handleTag(dataTomorrow.getInt(dataTomorrow.getColumnIndex("done")), startTime, endTime, false)
            val textViewText = TextView(context)
            val textViewStatus = TextView(context)
            val textViewTime = TextView(context)
            textViewText.text = text
            textViewStatus.text = done
            textViewTime.text = if (!startTime.isEmpty()) "$startTime - $endTime" else ""
            layoutTomorrowText.addView(textViewText)
            layoutTomorrowStatus.addView(textViewStatus)
            layoutTomorrowTime.addView(textViewTime)
        }
    }

    private fun setBackButtonListener() = backButton.setOnClickListener {
        finish()
    }

    private fun setClearButtonTodayListener() = clearButtonToday.setOnClickListener {
        db!!.deleteBy("date", LocalDate.now().toString())
        getTodayData()
        showToastMessage("Today items cleared...")
    }

    private fun setClearButtonTomorrowListener() = clearButtonTomorrow.setOnClickListener {
        db!!.deleteBy("date", LocalDate.now().plusDays(1).toString())
        getTomorrowData()
        showToastMessage("Tomorrow items cleared...")
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
