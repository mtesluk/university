package com.example.project

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_confirm.*
import android.content.Intent



class ConfirmActivity : AppCompatActivity() {
    private var db: DbHandler? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_confirm)
        db = DbHandler(this, "determination")

        val budle = intent.extras
        doneButton.setOnClickListener {
            db!!.updateDataBy("text",
                budle.getString("text"),
                "done",
                "1"
            )
            finish()
        }

        releasedButton.setOnClickListener {
            finish()
        }
    }
}
