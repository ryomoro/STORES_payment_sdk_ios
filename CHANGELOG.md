## 4.0.4 (2015-09-10)

変更点

* iOS 9 GM seed で、3 回連続スワイプ失敗するとアプリが強制終了する問題を修正
* Xcode 7 beta 6 でビルドした際の表示崩れ問題を修正 (#31)
* 画面遷移アニメーションがスライドでなく cross dissolve になっていた問題を修正

For internal use: Krona@c7f9266

## 4.0.3 (2015-08-26)

変更点

* 決済画面でキャンセルボタンを押した際に、coineyViewControllerDidCancel: デリゲートメソッドが呼ばれないバグを修正

For internal use: Krona@275caf2

## 4.0.2 (2015-08-04)

変更点

* 組み込み元アプリから、NSURLConnection で、http://coiney.com/ 等、ドメインのみ (パス無し) の URI に接続すると、例外が起こる問題を修正
* カードブランドのロゴ画像を改善

For internal use: Krona@49a3d0f
