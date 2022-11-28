package com.example.ssl2

import android.content.Intent
import android.os.Bundle
import android.widget.Button
import com.google.android.material.floatingactionbutton.FloatingActionButton
import com.google.android.material.snackbar.Snackbar
import androidx.appcompat.app.AppCompatActivity

class Simulate : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_simulate)
        setSupportActionBar(findViewById(R.id.toolbar))

        val btnSimulCheckpoint1 = this.findViewById<Button>(R.id.btn_simu1)
        btnSimulCheckpoint1.setOnClickListener{
            val intent = Intent(this@Simulate, ScanLuggage::class.java)
            intent.putExtra("check", "check1")
            startActivity(intent)
        }
        val btnSimulCheckpoint2 = this.findViewById<Button>(R.id.btn_simu2)
        btnSimulCheckpoint2.setOnClickListener{
            val intent = Intent(this@Simulate, ScanLuggage::class.java)
            intent.putExtra("check", "check2")
            startActivity(intent)
        }
        val btnSimulCheckpoint3 = this.findViewById<Button>(R.id.btn_simu3)
        btnSimulCheckpoint3.setOnClickListener{
            val intent = Intent(this@Simulate, ScanLuggage::class.java)
            intent.putExtra("check", "check3")
            startActivity(intent)
        }
    }


}