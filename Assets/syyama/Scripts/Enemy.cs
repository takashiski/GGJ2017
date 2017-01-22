/// <summary>
/// Enemyクラス
/// </summary>
public class Enemy {

    public byte _type { get; set; }           // 敵の種類
    public byte _position { get; set; }       // ポジション
    public byte _speed { get; set; }          // 敵の移動速度
    public byte _range_first { get; set; }    // 敵の移動開始位置
    public byte _range_last { get; set; }     // 敵の移動終了位置

    public Enemy(byte type, byte positoin, byte speed, byte range_first, byte range_last)
    {
        this._type = type;
        this._position = positoin;
        this._speed = speed;
        this._range_first = range_first;
        this._range_last = range_last;
    }

}
