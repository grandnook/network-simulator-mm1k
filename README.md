# M/M/1/K
情報ネットワークにおける単一待ち行列システムのイベント駆動型シミュレーション

> Note: なるべく C++ の機能を活用した実装を試みます．

# 待ち行列モデルによるモデル化

情報ネットワークシステムを確率過程に従う待ち行列モデルとしてモデル化するためには，以下の4つを規定する必要がある．

- 対象システムトポロジー
- パケット到着過程
- 通信処理時間分布
- 待ち行列規律

# 確率過程

### 指数分布（exponential distribution）
##### 確率分布関数（累積分布関数）
```math
A(t) = P[\tilde{t} \le t] = \left\{
    \begin{array}{ll}
    1 - e^{-\lambda t} & (t \ge 0) \\
    0 & (t \lt 0)
    \end{array}
\right.
```
##### 確率密度関数
```math
a(t) = \left\{
    \begin{array}{ll}
    \lambda e^{-\lambda t} & (t \ge 0) \\
    0 & (t \lt 0)
    \end{array}
\right.
```

##### 指数分布に従う確率変数の取得
指数分布に従う確率変数 $x \sim Exp(\lambda)$ を生成するためには，$A(t) \sim U(0,1)$ と仮定して，逆関数法で求めることができる．ただし，$U(0,1)$ は $0 \sim 1$ の一様乱数である．
```math
x = t = -\frac{\log \left( 1 - A(t) \right)}{\lambda} \,\,\,\,\, \left( = -\frac{1}{\lambda} \ln U \right)
```
# 待ち行列規則

- FIFO (First In First Out): 先着順サービス
- LIFO (Last In First Out): 後着順サービス
- Priority (優先度): 優先度の高いものから順にサービス
- Time Sharing: 時分割で処理リソースを割り当てる

今回は，最も基本的かつ一般的な規律であるFIFOを適用する．


# ケンドール記法
□/□/□/□ $\Leftrightarrow$ (1)/(2)/(3)/(4)

(1) 到着間隔分布
(2) サービス時間分布
> $M$ $\cdots$ 指数分布
> $D$ $\cdots$ 一定分布
> $E_k$ $\cdots$ $k$ステージにのアーラン分布
> $G$ $\cdots$ 一般分布
> $GI$ $\cdots$ 再生過程（間隔が独立な一般分布に従う過程）
> $IPP$ $\cdots$ 継続ポアソン過程 (Interrupted Poisson Process)
> $MMPP$ $\cdots$ マルコフ変調ポアソン過程

(3) サービス窓口の個数
(4) システム容量（省略した場合は$\infty$となる）

今回は，M/M/1/Kを対象とする．（プログラムの性質上，有限のシステム容量Kとなってしまう）

# 待ち行列モデルのシミュレーション
到着間隔分布とサービス時間分布を指数乱数により発生させ，待ち行列システム内のパケット数を増減させる．このような仮想的なシステムの動作に対して，パケット当たりの平均システム内時間や平均システム内パケット数などの各種統計量を取得する．


# 実行例
```bash
$ g++ run.cpp
$ ./a.out
```

警告が不要な場合
```bash
$ g++ -std=c++11 run.cpp
$ ./a.out
```