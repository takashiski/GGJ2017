using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy1 : MonoBehaviour {

    public float maxSpeed = 0f;

    public float destroyPos = -30f;
    private Rigidbody2D m_rigidbody2D;


    void Reset()
    {
        Awake();

        maxSpeed = 0f;
    }

    void Awake()
    {
        m_rigidbody2D = GetComponent<Rigidbody2D>();
    }

    // Update is called once per frame
    void Update () {
        m_rigidbody2D.velocity = new Vector2(-maxSpeed, m_rigidbody2D.velocity.y);

        // 一定ポジションに来たら敵オブジェクトを削除
        if(gameObject.transform.position.x <= destroyPos)
        {
            Destroy(gameObject);
        }
    }
}
