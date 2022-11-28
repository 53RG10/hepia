package com.example.ssl2

import android.content.Intent
import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.google.firebase.firestore.FirebaseFirestore


class Login : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_login)
        setSupportActionBar(findViewById(R.id.toolbar))

        val btnCreateProfile = this.findViewById<Button>(R.id.btn_create_new_user)
        btnCreateProfile.setOnClickListener {
            val intent = Intent(this@Login, Formular::class.java)
            startActivity(intent)
        }

        //button simulate
        val btnLogin = this.findViewById<Button>(R.id.btn_login)
        btnLogin.setOnClickListener {


            val login = findViewById<EditText>(R.id.txt_login_name)
            val password = findViewById<EditText>(R.id.txtp_pwd)


            if (login.text.trim().isEmpty()) {
                Toast.makeText(this, "Vous devez entrer votre nom d'identification.", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }
            if (password.text.trim().isEmpty()) {
                Toast.makeText(this, "Vous devez entrer votre mot de passe.", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }

            val db = FirebaseFirestore.getInstance()

            db.collection("Users")
                .get()
                .addOnCompleteListener { task ->
                    if (task.isSuccessful) {
                        for (document in task.result!!) {
                            if (document.data["login"] == login.text.toString() && document.data["password"] == password.text.toString()){
                                Log.wtf("DATAAAAA", document.id + " => " + document.data)
                                val intent = Intent(this@Login, CheckLuggage::class.java)
                                intent.putExtra("idUser", document.id)
                                startActivity(intent)
                            }else{
                                //Toast.makeText(this, "Login ou mot de passe invalid.", Toast.LENGTH_SHORT).show()
                            }
                        }
                    } else {
                        Log.wtf("truc", "Error getting documents.", task.exception)
                    }
                }
        }

    }
}