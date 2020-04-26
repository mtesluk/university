package com.example.project

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import com.github.mikephil.charting.data.BarData
import com.github.mikephil.charting.data.BarDataSet
import com.github.mikephil.charting.data.BarEntry
import kotlinx.android.synthetic.main.activity_stats.*
import com.github.mikephil.charting.formatter.IndexAxisValueFormatter
import java.time.LocalDate


class StatsActivity : AppCompatActivity() {
    private var db: DbHandler? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_stats)
        db = DbHandler(this, "determination")

        setChart()
        setBackButtonListener()
    }

    private fun setChart() {
        val chartEntry: ArrayList<BarEntry> = arrayListOf()
        val datesEntry: ArrayList<String> = arrayListOf()
        for (i in 0 until Config.CHART_DAY_COUNT) {
            val date = LocalDate.now().plusDays(-1*i.toLong()).toString()
            datesEntry.add(date)

            val dataDate = db!!.getDataBy("date", date)
            var sum = 0
            var count = 0
            while(dataDate.moveToNext()) {
                if (dataDate.getString(dataDate.getColumnIndex("start_time")).isNotEmpty()) {
                    sum += dataDate.getString(dataDate.getColumnIndex("done")).toInt()
                    count += 1
                }
            }
            var per = 0f
            if (count != 0) per = (sum/count.toFloat() * 100)

            chartEntry.add(BarEntry(i.toFloat(), per))
        }

        val chartDataSet = setDataSet(chartEntry)
        setChartSettings(datesEntry, chartDataSet)
    }

    private fun setChartSettings(datesEntry: ArrayList<String>, chartDataSet: BarDataSet) {
        setAxis(datesEntry)

        chart.data = BarData(chartDataSet)
        chart.legend.isEnabled = false
        chart.description.isEnabled = false
        chart.setTouchEnabled(false)
        chart.setScaleEnabled(false)
    }

    private fun setDataSet(chartEntry: ArrayList<BarEntry>): BarDataSet {
        val chartDataSet = BarDataSet(chartEntry, "Dates")
        chartDataSet.setDrawValues(false)

        return chartDataSet
    }

    private fun setAxis(datesEntry: ArrayList<String>) {
        chart.axisLeft.axisMaximum = 100f
        chart.axisLeft.axisMinimum = 0f
        chart.axisRight.isEnabled = false
        chart.xAxis.valueFormatter = IndexAxisValueFormatter(datesEntry)
        chart.xAxis.granularity = 1f
    }

    private fun setBackButtonListener() = backButton2.setOnClickListener {
        finish()
    }
}
