package com.example.firstapp

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.EditText
import java.time.temporal.TemporalAmount

class MainActivity : AppCompatActivity() {
    private lateinit var etBaseAmount: EditText

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        etBaseAmount = findViewById(etBaseAmount)
    }
}