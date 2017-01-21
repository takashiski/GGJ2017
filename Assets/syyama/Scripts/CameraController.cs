using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Camera))]
public class CameraController : MonoBehaviour {

    private Camera m_camera;

    //これ以上移動しないカメラの位置
    private float cameraStartPos = -10;
    private float cameraEndPos = 100;

    void Awake()
    {
        m_camera = GetComponent<Camera>();
    }

    // Update is called once per frame
    void Update () {

        // 入力の受付
        float x = Input.GetAxis("Horizontal");
        
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
}
