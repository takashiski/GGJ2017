using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Camera))]
public class CameraController : MonoBehaviour {

    private Camera m_camera;

    //これ以上移動しないカメラの位置
    private float cameraStartPos = 0f;
    private float cameraEndPos = 150f;

    private bool initCamera = false;

    void Awake()
    {
        m_camera = GetComponent<Camera>();
    }

    // Update is called once per frame
    void Update() {

        // カメラの初期処理
        if(!initCamera)
        {
            InitCamera();
            return;
        }

        // 入力の受付
        var x = Input.GetAxis("Horizontal");
        
        var pos = m_camera.transform.position;

        // カメラの位置移動
        if (Mathf.Abs(x) > 0)
        {
            m_camera.transform.position = new Vector3(pos.x + x / 1.5f, pos.y, pos.z);
        }

        // カメラの位置をこれ以上いかないようにする
        if (pos.x < cameraStartPos)
        {
            m_camera.transform.position = new Vector3(cameraStartPos, pos.y, pos.z);
        }
        if (pos.x > cameraEndPos)
        {
            m_camera.transform.position = new Vector3(cameraEndPos, pos.y, pos.z);
        }
    }

    /// <summary>
    /// カメラを初期位置にもっていく
    /// </summary>
    void InitCamera()
    {
        var pos = m_camera.transform.position;

        if (pos.x < 50f)
        {
            m_camera.transform.position = new Vector3(pos.x + 0.4f, pos.y, pos.z);
        }
        else
        {
            initCamera = true;
        }
    }
}
