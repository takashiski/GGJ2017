﻿using UnityEngine;
using System.IO.Ports;
using System.Threading;

public class SerialHandler : MonoBehaviour
{
    public delegate void SerialDataReceivedEventHandler(string message);
    public event SerialDataReceivedEventHandler OnDataReceived;

    public string portName = "COM3";
    public int baudRate = 9600;

    private SerialPort serialPort_;
    private Thread thread_;
    private bool isRunning_ = false;

    private string message_;
    private bool isNewMessageReceived_ = false;

    void Awake()
    {
        Open();
    }

    void Update()
    {
        //if (isNewMessageReceived_)
        //{
        //    OnDataReceived(message_);
        //}
    }

    void OnDestroy()
    {
        Close();
    }

    private void Open()
    {
        serialPort_ = new SerialPort(portName, baudRate, Parity.None, 8, StopBits.One);
        serialPort_.Open();

        isRunning_ = true;

        thread_ = new Thread(Read);
        thread_.Start();
    }

    private void Close()
    {
        isRunning_ = false;

        //if (thread_ != null && thread_.IsAlive)
        //{
        //thread_.Join();
        thread_.Abort();
        //}

        //if (serialPort_ != null && serialPort_.IsOpen)
        //{
            serialPort_.Close();
            serialPort_.Dispose();
        //}
    }

    /// <summary>
    /// シリアライズを読み込む
    /// </summary>
    private void Read()
    {
        //while (isRunning_ && serialPort_ != null && serialPort_.IsOpen)
        //{
        //    try
        //    {
        //        //if (serialPort_.BytesToRead > 0)
        //        //{
        //            message_ = serialPort_.ReadLine();
        //            isNewMessageReceived_ = true;
        //        //}
        //    }
        //    catch (System.Exception e)
        //    {
        //        Debug.LogWarning(e.Message);
        //    }
        //}
        //Thread.Sleep(1);
    }

    /// <summary>
    /// シリアライズを書き込む
    /// </summary>
    /// <param name="message"></param>
    public void Write(string message)
    {
        try
        {
            serialPort_.Write(message);
        }
        catch (System.Exception e)
        {
            Debug.LogWarning(e.Message);
        }
    }

    /// <summary>
    /// シリアライズを書き込む
    /// </summary>
    /// <param name="buffer"></param>
    public void Write(byte[] buffer)
    {
        try
        {
            serialPort_.Write(buffer, 0, buffer.Length);
        }
        catch (System.Exception e)
        {
            Debug.LogWarning(e.Message);
        }
    }
}