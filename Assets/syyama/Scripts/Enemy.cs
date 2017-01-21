/// <summary>
/// Enemyクラス
/// </summary>
public class Enemy {

    public int type { get; set; }
    public int speed { get; set; }
    public int range_first { get; set; }
    public int range_last { get; set; }
    public int position { get; set; }

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="type"></param>
    /// <param name="speed"></param>
    /// <param name="range_first"></param>
    /// <param name="range_last"></param>
    /// <param name="position"></param>
    public Enemy(int type, int speed, int range_first, int range_last, int position)
    {
        this.type = type;
        this.speed = speed;
        this.range_first = range_first;
        this.range_last = range_last;
        this.position = position;
    }

}
