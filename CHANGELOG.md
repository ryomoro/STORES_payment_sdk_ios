## 5.0.1 (2016-09-15)

### 変更点

#### バグ修正

* iOS 10でアプリ初回起動時にペアリング済みのターミナルやプリンターに再接続しないバグを修正しました。

#### ATS設定

* Info.plistでApp Transport Securityの設定をお願いしていましたが、不要になりましたので、削除頂けます。
* 利用規約ページをHTTPで取得していましたが、HTTPSに移行しました。

#### Git LFS

* Bitcode対応によりライブラリが大きくなってしまったため、Git Large File Storageを導入しました。
* お手数ですが、 https://git-lfs.github.com よりgit-lfsをインストール頂きますようお願い致します。

## 5.0.0 (2016-09-06)

### 変更点

#### レシート印刷

* レシート印刷機能オフ時に、[レシートを印刷] ボタンを非表示にしました。
* レシート印刷機能をオンにするには、 `-[UIApplicationDelegate application:didFinishLaunchingWithOptions:]` で、 `CYEnablePrinting(YES)` を呼んでください。対応プリンターとペアリングしておくことで、決済完了および売上詳細画面からレシート印刷が可能になります。対応プリンターは弊社サイトをご参照ください。
* BLE接続のスター精密SM-L200は、CoineyKitでは現在ご利用いただけません。ご了承ください。
* 自社アプリでレシート印刷を実装される場合は、 `CYEnablePrinting(YES)` を呼ばないでください。 `EASession` を共有できないためです。
* 新たに、EPSON TM-m30に対応しました。

#### CoineyViewControllerのinitメソッド簡素化

* 従来は `CoineyViewController` の `init` メソッドは `CYItem` の配列をパラメータとしていましたが、金額とメモだけを渡すようになりました。
* お手数ですが、新APIを使用するよう修正をお願いします。

#### 売上取消・返品

* APIメソッドにより売上取消・返品確認画面を出せるようになりました。
* `CYTransactionViewController` 表示後、 `-confirmRefundWithCompletion:` を呼び出してください。

#### その他

* Bitcodeに対応
* iOS 10に対応
* Coineyリーダー (磁気リーダー) の対応を終了
* 暗証番号誤入力回数オーバーのICカードを使用した際に、適切なエラーメッセージを表示
* 位置情報の許可がオフでも決済できてしまう場合があるバグを修正
* iPadで決済完了画面でキーボードを切り替えた時の表示崩れを修正

## 4.2.3 (2016-05-19)

### 変更点

* 支払い画面右上に、ターミナル情報を追加
* サイン時のターミナル表示を、「アプリを操作してください」→「サインしてください」に改善
* iOS 7 で checkAuthenticationStatus を使用すると強制終了するバグを修正
* 契約外ブランドのカードを使おうとすると、ダイアログが二重に表示されるバグの修正
* iPad、iPhone 6、iPhone 6 plus で、取引詳細画面のラベル位置を修正

## 4.2.2 (2016-03-11)

### 変更点

* カード番号直接入力でクラッシュする問題を修正 (#42)
* ターミナル画面の日本語化に対応
* 稀に「決済金額は¥100以上です」と出て決済できない場合がある問題を修正
* 英語ローカリゼーションを削除し、日本語のみの提供に

For internal use: Krona@7555285

## 4.2.1 (2016-01-12)

### 変更点

* 一部の他社製 IC 決済モジュールをリンクすると、シンボル衝突が起こる問題を修正

For internal use: Krona@f6e4e42.

## 4.2.0 (2015-12-08)

#### 変更点

* CoineyターミナルでのIC・磁気カード決済に対応しました。

#### 注意点

##### External Accessory Protocol の追加

ターミナルとのBluetooth接続のため、アプリの Info.plist に、下記の記述を追加してください。

```
<key>UISupportedExternalAccessoryProtocols</key>
<array>
  <string>com.coiney.Coiney</string>
</array>
```

また、iTunes Connect で App Store へレビュー申請する際、MFi PPID が必要になります。

詳しくは Apple MFi プログラムのドキュメントをご参照ください。

##### 支払いキャンセル時のメッセージについて

PIN入力画面で、[支払いキャンセル] を押すと、利用可能なカードの場合でも、「このカードはお使いいただけません」と表示されます。メッセージの内容に誤りがありますが、支払いのキャンセルは問題なく行われております。

For internal use: Krona@4c21b63

## 4.1.1 (2015-10-20)

#### 変更点

* ZipArchive を使用しているアプリで、CoineyKit の ZipArchive とシンボル衝突が発生する問題を修正 (#34)
* CYTransactionViewController の「返金済み」の行が表示されない問題を修正 (#35)
* Example アプリ + iOS 7 で、決済完了後に取引詳細画面が表示されない問題を修正

For internal use: Krona@f0ba548

## 4.1.0 (2015-10-02)

#### 新機能

* Xcode 7 + iOS 9 に対応
* 決済完了画面のレイアウト改善
* iOS 9 で番号直接入力時にカード番号が見切れる問題を修正 (#33)

#### 注意点

##### App Transport Security について

App Transport Security 対応 (#32) のため、アプリの Info.plist に、下記の値を追加してください。これがないと、「ネットワークエラー」となりログインできません。


```
<key>NSAppTransportSecurity</key>
<dict>
  <key>NSExceptionDomains</key>
  <dict>
    <key>coiney.com</key>
    <dict>
      <key>NSExceptionAllowsInsecureHTTPLoads</key>
      <true/>
      <key>NSIncludesSubdomains</key>
      <true/>
    </dict>
  </dict>
</dict>
```

今後、値の追加をしなくてもいいように、https に移行して参りますが、お手数ですが暫定策としてご対応願います。

※ httpで取得するのは初回ログイン時に表示される利用規約のみで、その他決済関連の通信には https を使用しておりますのでご安心ください。

##### Bitcode 対応

現状、bitcode には対応しておりません。

##### GenerateDSYMFile

ビルド中 GenerateDSYMFile で大量のワーニングが発生する場合は、Xcode のビルド設定を下記のように変更してください。

Debug Configuration:

```
DEBUG_INFORMATION_FORMAT = dwarf;
DEPLOYMENT_POSTPROCESSING = NO;
GCC_GENERATE_DEBUGGING_SYMBOLS = YES;
GCC_SYMBOLS_PRIVATE_EXTERN = NO;
```

Release Configuration:

```
DEBUG_INFORMATION_FORMAT = "dwarf-with-dsym";
DEPLOYMENT_POSTPROCESSING = YES;
GCC_GENERATE_DEBUGGING_SYMBOLS = NO;
GCC_SYMBOLS_PRIVATE_EXTERN = YES;
```

##### 動作環境

* ビルドには Xcode 7.x をお使いください。
* 対象 iOS バージョンは、引き続き、「7.0 以上」です。
* 対応画面サイズは、引き続き、3.5"、4.0"、4.7"、5.5"、iPad です。

For internal use: Krona@18facc6

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

For internal use: Krona@18facc6
