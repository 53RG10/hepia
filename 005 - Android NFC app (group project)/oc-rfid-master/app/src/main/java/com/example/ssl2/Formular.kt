package com.example.ssl2

import android.content.Intent
import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.google.firebase.firestore.FirebaseFirestore


class Formular : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_formular)
        setSupportActionBar(findViewById(R.id.toolbar))

        // Access a Cloud Firestore instance from your Activity
        val db = FirebaseFirestore.getInstance()

        val btnAddUser = this.findViewById<Button>(R.id.btn_form_addUser)
        btnAddUser.setOnClickListener {
            val name = findViewById<EditText>(R.id.txt_form_name)
            val email = findViewById<EditText>(R.id.txt_form_mail)
            val login = findViewById<EditText>(R.id.txt_form_login)
            val password = findViewById<EditText>(R.id.txt_form_pwd)

            if (name.text.trim().isEmpty()) {
                Toast.makeText(this, "Vous devez entrer votre nom.", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }

            if (email.text.trim().isEmpty()) {
                Toast.makeText(this, "Vous devez entrer votre email.", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }

            if (login.text.trim().isEmpty()) {
                Toast.makeText(this, "Vous devez entrer votre nom de login.", Toast.LENGTH_SHORT)
                    .show()
                return@setOnClickListener
            }

            if (password.text.trim().isEmpty()) {
                Toast.makeText(this, "Vous devez enter votre mot de passe.", Toast.LENGTH_SHORT)
                    .show()
                return@setOnClickListener
            }

            val user = UsersData(
                name.text.toString(),
                email.text.toString(),
                login.text.toString(),
                password.text.toString(),
                null
            )

            db.collection("Users").add(user)
                .addOnSuccessListener { documentReference ->
                    Log.wtf("Success Firbase", "user")
                    val intent = Intent(this@Formular, CheckLuggage::class.java)
                    intent.putExtra("idUser", documentReference.id)
                    startActivity(intent)
                }
                .addOnFailureListener { e ->
                    Log.wtf("Failed Firebase", "user")
                }

            db.collection("Users")
                .get()
                .addOnCompleteListener { task ->
                    if (task.isSuccessful) {
                        for (document in task.result!!) {
                            Log.d("NONEasdf", document.id + " => " + document.data)
                        }
                    } else {
                        Log.w("NONEasdf", "Error getting documents.", task.exception)
                    }
                }
        }

    }
}