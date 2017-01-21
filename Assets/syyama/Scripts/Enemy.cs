/// <summary>
/// Enemyクラス
/// </summary>
public class Enemy {

    public int type { get; set; }           // 敵の種類
    public int status { get; set; }         // 敵の現在の状態
    public int speed { get; set; }          // 敵の移動速度
    public int range_first { get; set; }    // 敵の移動開始位置
    public int range_last { get; set; }     // 敵の移動終了位置
    public int size { get; set; }           // 敵のサイズ

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="type">敵の種類</param>
    /// <param name="status">敵の現在の状態</param>
    /// <param name="speed">敵の移動速度</param>
    /// <param name="range_first">移動開始位置</param>
    /// <param name="range_last">移動終了位置</param>
    /// <param name="position">敵のサイズ</param>
    public Enemy(int type, int status, int speed, int range_first, int range_last, int size)
    {
        this.type = type;
        this.speed = speed;
        this.range_first = range_first;
        this.range_last = range_last;
        this.size = size;
    }

}
