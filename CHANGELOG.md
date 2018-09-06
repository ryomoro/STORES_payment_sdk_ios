## 5.3.3 (2018-09-06)

支払方法選択画面のキャンセル押下で `coineyViewControllerDidCancel` が呼び出されない問題に対応しました。
* 磁気カード決済で、売上詳細画面に表示乱れが発生するバグを修正しました。
* WeChat Payのレシートに、レシートコメントが印刷されない問題に対応しました。

## 5.3.2 (2018-08-30)

* Xcode で libstdc++ が非推奨になったため、libc++ に移行しました。libc++ をリンクするよう、ビルド設定の変更をお願いいたします。
* Rolto PT10 レシートプリンターの対応を終了しました。
* サンプルアプリで SII 製プリンターが使えるようになりました。

## 5.3.1 (2018-05-23)

### バグ修正

* Swiftファイルで `import CoineyKit` をすると、 `error: missing required modules...` が発生する問題を修正しました。
* 一部Bitcodeに対応していない部分があったため、Bitcode有効のプロジェクトでリンカーエラーが発生する問題を修正しました。

### 改善点

* v5.3.0の「重要なお知らせ」にて、Objective-Cプロジェクトに空のSwiftファイル追加のお願いをしておりましたが、本バージョンでは不要となります。

## 5.3.0 (2018-05-17)

### 重要なお知らせ

* 動作環境が、iOS 8以上→iOS 9以上に変更になりました。アプリのDeployment Targetが9.0未満の場合は、本バージョンはご利用いただけません。
* `libxml` 関連のリンカーエラーが出る場合は、ターゲットのLinked Frameworks and Librariesの設定で、 `libxml2.tbd` を追加してください。
* Swiftファイルが一つも存在しないターゲットではビルド時にリンカーエラーが発生するため、空のSwiftファイルを一つプロジェクトに追加する必要があります。本リポジトリのObjective-C版サンプルアプリに `File.swift` という空ファイルが追加されておりますので、そちらを参考にしてください。

### 新機能

* レシートプリンター SII MP-B20に対応しました。
* レシートプリンター SII RP-D10、RP-E10/E11 (80mm感熱紙のみ) に対応しました。

### 改善・変更点

* テストアカウントでWeChatテストQRコードで決済できるようになりました。テストQRコード: https://coiney.com/qrtest
* 軽微なUI/UXの改善を行いました。

## 5.2.1 (2018-05-15)

### iOS 11.2.6以降でCoineyターミナルとBluetooth接続できない問題を修正

* iOS 11.2.6以降+CoineyKit 5.2.0以前でCoineyターミナルとBluetooth接続できない問題に対応しました。
* CoineyKitをアップデートしても接続できない場合は、 [こちらのページ](https://support.coiney.com/hc/ja/articles/360001901231--iOS-v11-2-6以降のOS端末をご利用中の方へ) の「2. アプリを最新にしてもペアリングができない」の手順に従い、端末のリセットをお願い致します。

### メモリ逼迫時のクラッシュを修正

* `UIApplicationDidReceiveMemoryWarningNotification` が発生した際にクラッシュする問題を修正しました。
* 次の例外への対応になります: `+[CYAPI didReceiveMemoryWarning]: unrecognized selector sent to instance...`

## 5.2.0 (2017-10-06)

### American ExpressおよびDinersカードのIC決済に対応

* 同ブランドについては、磁気フォールバックによる決済に対応しておりましたが、より安全性の高い、ICリーダーによる決済に対応しました。
* ブランド規約に準拠するため、レシートのレイアウトが一部変わりました。
  * 暗証番号を入力し、サインが省略された場合「暗証番号確認済みのためサインを省略しました」という文言を追加
  * 端末識別番号を追加

### その他改善点

* ターミナルとのペアリング手順が、動画付きでわかりやすくなりました。
* 売上取消・返品時の確認画面の文言を、Web管理画面と統一しました。
* 売上取消・返品時に、自動印刷がオンになっていれば、自動で取消レシートが印刷されるようになりました。

## 5.1.1 (2017-07-25)

### 変更点

* CoineyKit決済画面表示時に、WeChat Pay審査状況など、契約状況を最新の状態に更新するようにしました。これにより、WeChat Payの審査通過後、ログアウト→再ログイン頂かなくてもWeChat Payが利用できるようになりました。
* 支払回数選択画面および返金確認画面の文言を微調整しました。

## 5.1.0 (2017-05-31)

### WeChat Pay対応

WeChat Pay受付開始に向け、QR読取りによるWeChat Payの決済機能を追加しました。※受付開始時期については、別途アナウンスいたします。

WeChat Pay対応店舗では、CoineyKit起動時に「決済方法選択」画面が表示され、クレジットカード・WeChat Payから選択できます。WeChat Pay非対応店舗では、カード決済画面が開きますので、従来の動きと変わりません。

決済方法選択画面をスキップする方法も用意しています。詳しくは `CYCoineyViewController` のドキュメントをご参照ください。

動作確認用にテストアカウントを発行しますので、ご希望の方は coineykitsupport@coiney.com までお問い合わせください。

##### 注意事項

`CYTransaction` で `paymentMethod` プロパティが `CYPaymentMethodWechatPay` の場合、 `cardSuffix`、`approvalCode` の各プロパティが `nil` となります。 `nil` チェックなど、適宜対応いただきますようお願いします。WeChat Pay受付開始に伴い、旧CoineyKitバージョンでも上記プロパティに `nil` が返ります。

### プリンター設定

* CoineyKitのレシート印刷機能を使用する場合 (`CYEnablePrinting(YES)` を呼ぶ場合)、CoineyKit上からプリンターに接続したり、設定を確認できるようになりました。カード決済画面およびWeChat Pay QR読取り画面の右上部のボタンを押すと開きます。
* `CYEnablePrinting(YES)` を呼ばない場合は、プリンター設定は非表示となります。
* Bluetooth LE接続の、スター精密 SM-L200 に対応しました。※SM-L200は接続方法が異なるため、プリンター設定からの接続のみ対応しており、iOSのBluetooth設定からは接続できません。

### バグ修正

* スタッフアカウントでログインすると、取消していないにも関わらず `CYTransactionViewController` の売上取消ボタンに「売上取消・返品済み」と表示される問題を修正しました。

## 5.0.2 (2017-03-14)

### 変更点

* 稀に「決済額は¥100以上です」と出て決済できない問題を修正
* サインを書きやすいように、iPadのサイン画面を全画面に
* PINとサインを両方求めるカードを使った時に、決済完了できない問題を修正
* 最低OSバージョンを、iOS 7.0→iOS 8.0に変更
* プリンターに再接続する際に稀に起きるクラッシュを修正
* ログイン画面のパスワード忘れおよび新規登録ボタンを押しやすいように、大きく
* 決済額上限を超えるIC決済で適切なエラーメッセージを表示
* 売上詳細のUI改善

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
