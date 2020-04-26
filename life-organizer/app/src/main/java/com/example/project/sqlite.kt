package com.example.project
import android.content.ContentValues
import android.content.Context
import android.database.Cursor
import android.database.sqlite.*


class DbHandler(context: Context, private val tableName: String):
        SQLiteOpenHelper(context, DATABASE_NAME, null, DATABASE_VERSION) {

    override fun onCreate(db: SQLiteDatabase) {
        val createTable: String = "CREATE TABLE $tableName (ID INTEGER PRIMARY KEY AUTOINCREMENT," +
                "start_time TEXT, end_time TEXT, text TEXT, date TEXT, done INTEGER)"
        db.execSQL(createTable)
    }
    override fun onUpgrade(db: SQLiteDatabase, oldVersion: Int, newVersion: Int) {
        val drop = "DROP TABLE IF EXISTS $tableName"
        db.execSQL(drop)
        onCreate(db)
    }
    override fun onDowngrade(db: SQLiteDatabase, oldVersion: Int, newVersion: Int) {
        onUpgrade(db, oldVersion, newVersion)
    }

    fun addData(start_time: String, end_time: String, text: String, date: String, done: Number) {
        val db: SQLiteDatabase = writableDatabase
        val query = "INSERT INTO $tableName (" +
                "start_time, " +
                "end_time," +
                "text," +
                "date," +
                "done" +
                ")\n" +
                "VALUES ('$start_time', '$end_time', '$text', '$date', '$done')"
        db.execSQL(query)
    }

    fun getAllData(): Cursor {
        val db = writableDatabase
        val query = "SELECT * FROM $tableName"
        var data = db.rawQuery(query, null)
        return data
    }

    fun updateDataBy(columnWhere: String, valueWhere: String, columnTo: String, valueTo: String) {
        val db = writableDatabase
        val query = "UPDATE $tableName SET $columnTo = '$valueTo' WHERE $columnWhere = '$valueWhere'"
        db.execSQL(query)
    }

    fun getDataBy(column: String, value: String): Cursor {
        val db = writableDatabase
        val query = "SELECT * FROM $tableName WHERE $column = '$value'"
        return db.rawQuery(query, null)
    }

    fun deleteAll() {
        val db = writableDatabase
        val query = "DELETE FROM $tableName"
        db.execSQL(query)
    }

    fun deleteBy(column: String, value: String) {
        val db = writableDatabase
        val query = "DELETE FROM $tableName WHERE $column = '$value'"
        db.execSQL(query)
    }

    fun isTableEmpty(): Boolean {
        val db = writableDatabase
        val query = "SELECT * FROM $tableName"
        val data = db.rawQuery(query, null)
        return data.count == 0
    }

    companion object {
        // If you change the database schema, you must increment the database version.
        const val DATABASE_VERSION = 1
        const val DATABASE_NAME = "FeedReader.db"
    }
}