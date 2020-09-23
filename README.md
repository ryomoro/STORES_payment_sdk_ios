[![Build Status](https://travis-ci.com/Coiney-SDK/CoineyKit-iOS.svg?token=q1fWSqJB3688yqHv3sZs&branch=master)](https://travis-ci.com/Coiney-SDK/CoineyKit-iOS)

# CoineyKit

CoineyKit をご利用いただき、ありがとうございます。ご要望やバグ報告の際は、お手数ですが [GitHub issue](https://github.com/Coiney-SDK/CoineyKit-iOS/issues) を作成いただきますようお願い致します。


## 電子マネー決済対応版SDK公開のお知らせ（2020−07−07）

STORESターミナルSDK（旧CoineyKit）で、電子マネー決済の利用が可能になりました。※セミセルフ、セルフレジには非対応です。

以下注意事項となりますのでご確認ください。

**1.  電子マネー決済のご利用方法について**
- 電子マネー（交通IC）で決済できる金額は100〜20,000円までになります。

- 電子マネー（交通IC）では取消・返品が行えません。返金される場合は現金でご対応下さい。

- SDKでは以下の機能が実装されていないため、STORESターミナルアプリのインストールが必要になります。
  - 残高照会（SuicaやPASMOの残高金額を確認する機能）
  - 処理未了の確認。処理未了が発生した場合はSTORESターミナルアプリより取引が成立しているかご確認下さい。

- チャージは行なえません。残高不足の場合は取引を中止し、その他の決済方法で取引して下さい。

- 対応機種はiOSのみとなります。

**2．テストアカウントについて**
- ご希望の方はstores_terminal_sdk@hey.jp までご連絡ください。

**3．電子マネーご利用時のお願い**
- その他ご注意事項がございますので、ご利用頂く際には一度上記メールアドレスまでご連絡ください。

****

## サービス名称変更のお知らせ 〜「Coiney」から「STORESターミナル」へ〜 ( 2020-04-27 )

コイニー株式会社は、2020年4月27日より順次、お店のキャッシュレスサービス「Coiney（コイニー）」のサービス名称を、「STORES（ストアーズ）ターミナル」に変更いたします。

「CoineyKit」は今後のリリースにて「STORESターミナルSDK」へ名称が変更になりますが、現在最新版の SDK は旧サービス名称表記のまま引き続きご利用可能です。

-------

# サンプルアプリ

## 目的

このチュートリアルでは、CoineyKitを使って、カード決済ができるサンプルアプリを作成します。

(完成したものが `Example/` 配下にあります)

## 必要なもの

あらかじめ [git-lfs](https://git-lfs.github.com) をインストールし、 `git lfs install` を実行してください。git-lfs がないと、リポジトリを正しくクローンできません。

 * CoineyKit (このリポジトリを `git clone` してください)
 * Xcode 11
 * Coineyターミナル (購入については、 <coineykitsupport@coiney.com> までお問い合わせください)

## プロジェクトのセットアップ

Xcode を起動し、`File → New → Project` から、`Single View Application` を選択します。

![Template selection](.readme_images/template-selection.png)

下記のように設定します。

![Template options](.readme_images/template-options.png)

本リポジトリを `git clone` し、`CoineyKit` フォルダを、`«プロジェクトフォルダ»/CoineyKit` となるように、プロジェクトフォルダの中へコピーします。

![Folder hierarchy](.readme_images/folder-hierarchy.png)

Git をお使いでしたら、更新しやすいように、submodule として追加することをお勧めします。

`CoineyKit.xcconfig` と `CoineyKitResources.bundle` を、Xcode のプロジェクトナビゲーターにドラッグ＆ドロップします。

次に、Debug・Release 両方の configuration に "CoineyKit" を指定してください。

![Configurations](.readme_images/configuration.png)

ターゲットの General 設定を開き、`CoineyKit.framework` と `CoineyKit.framework/Frameworks/TCMPayment.framework` をリンクします。

![Libraries and Frameworks](.readme_images/frameworks-libs2.png)

もう少しでセットアップは完了です。

#### Info.plist への追加

BluetoothでCoineyターミナルに接続し、ICや磁気カード決済をするために、`UISupportedExternalAccessoryProtocols` をInfo.plistへ追加する必要があります。

```xml
<key>UISupportedExternalAccessoryProtocols</key>
<array>
  <string>com.coiney.Coiney</string>
</array>
```



## 初期化をする

CoineyKitを初期化するために prepare メソッドを呼んでください。
また、引数にはCoineyKitを使用する画面のViewControllerを渡してください。
注) viewDidLoad() など、画面が表示する前に prepare メソッドを呼び出すと正常に動作しない場合があります。

### Objective-C

`ViewController.m` を開き、下記のコードを貼り付けてください。

#### ViewController.m

```objective-c
(void)viewDidAppear:(BOOL)animated
{
  [super viewDidAppear:animated];

  [CYKit prepareInController:self];
}
```

### Swift

`ViewController.swift` を開き、下記のコードを貼り付けてください。

#### ViewController.swift

```swift
override func viewDidAppear(_ animated: Bool) {
    super.viewDidAppear(animated)
    
    CYKit.prepare(in: self)
}
```


## 決済をする

### Objective-C

`ViewController.h` と `ViewController.m` を開き、下記のコードを貼り付けてください。

#### ViewController.h

```objective-c
#import <UIKit/UIKit.h>

@interface ViewController : UIViewController
@property(weak, nonatomic) IBOutlet UITextField *productMemoField, *productPriceField;

- (IBAction)makePayment:(id)aSender;
@end
```

#### ViewController.m

```objective-c
#import "ViewController.h"
@import CoineyKit;

@implementation ViewController

- (IBAction)makePayment:(id)aSender
{
    NSString *memo = _productMemoField.text;
    int price = [_productPriceField.text intValue];

    // CYCoineyViewController のインスタンスを作成
    CYCoineyViewController * coineyController = [[CYCoineyViewController alloc] initWithAmount:price memo:memo];

    // ViewController の上に表示
    [self presentViewController:coineyController animated:YES completion:nil];
}
@end
```


​    
### Swift

#### ViewController.swift

```swift
import UIKit
import CoineyKit

class ViewController: UIViewController {

    @IBOutlet weak var memoField: UITextField!
    @IBOutlet weak var amountField: UITextField!
    
    @IBAction func makePayment(sender: AnyObject) 
    {
        let memo = productNameField.text ?? ""
        let amount = Int64(productPriceField.text!) ?? 0
        
        // CYCoineyViewController のインスタンスを作成
        guard let coineyController = CYCoineyViewController.init(amount: amount, memo: memo) else {
            fatalError("Failed to initialize CYCoineyViewController.")
        }
        
        // ViewController の上に表示
        self.present(coineyController, animated: true, completion: nil)
    }
}
```

`Main.storyboard` でボタンを作り、押されたら `makePayment:` が呼び出されるようにしてください。`productNameField` と `productPriceField` はそれぞれ `IBOutlet` をフィールドにつなげてください。

![Action connection](.readme_images/action-connection.png)

iPhone で実行すると、下記のようになります。

![App screenshot](.readme_images/simshot1.png)

あとはターミナルを繋げば決済できます。ターミナルへ接続するには、ナビゲーションバー右側のターミナル情報ボタンをタップし、[ターミナルに接続する] をタップしてください。

## 結果の通知を受け取る

### Objective-C

デリゲートメソッドを使って、決済完了時とキャンセル時に通知を受け取ることができます。下記のように、`ViewController.m` に `CYCoineyViewControllerDelegate` プロトコルを実装させ、`coineyViewController:didCompleteTransaction:` および `coineyViewControllerDidCancel:` を実装してください。

#### ViewController.m

```objective-c
#import "ViewController.h"
@import CoineyKit;

@interface ViewController () <CYCoineyViewControllerDelegate>
@end

@implementation ViewController

- (IBAction)makePayment:(id)aSender
{
    NSString *memo = _productNameField.text;
    NSInteger amount = [_productPriceField.text integerValue];

    // CYCoineyViewController のインスタンスを作成
    CYCoineyViewController * coineyController = [[CYCoineyViewController alloc] initWithAmount:amount memo:memo];
    coineyController.delegate = self;
    
    // ViewController の上に表示
    [self presentViewController:coineyController animated:YES completion:nil];
}

- (void)coineyViewController:(CYCoineyViewController *)aController
      didCompleteTransaction:(id<CYTransaction>)aTransaction
{
    NSLog(@"Completed transaction: %@", aTransaction);
}

- (void)coineyViewControllerDidCancel:(CYCoineyViewController *)aController
{
    [aController dismissViewControllerAnimated:YES completion:nil];
    NSLog(@"Cancelled payment.");
}
@end
```

### Swift

#### ViewController.swift

```swift
import UIKit
import CoineyKit

class ViewController: UIViewController {

    @IBOutlet weak var memoField: UITextField!
    @IBOutlet weak var amountField: UITextField!

    @IBAction func makePayment(sender: AnyObject) {
        let memo = productNameField.text ?? ""
        let amount = Int64(productPriceField.text!) ?? 0
        
        // CYCoineyViewController のインスタンスを作成
        guard let coineyController = CYCoineyViewController.init(amount: amount, memo: memo) else {
            fatalError("Failed to initialize CYCoineyViewController.")
        }
        coineyController.delegate = self
        
        // ViewController の上に表示
        self.present(coineyController, animated: true, completion: nil)
    }
}

extension ViewController : CYCoineyViewControllerDelegate {

    func coineyViewController(_ aController: CYCoineyViewController!,
                              didComplete aTransaction: CYTransaction!) {
        print("Completed transaction: \(aTransaction)")
    }

    func coineyViewControllerDidCancel(_ aController: CYCoineyViewController!) {
        self.dismiss(animated: true, completion: nil)
        print("Cancelled payment.")
    }
}
```

## 取引詳細の表示・売上取消

取引 ID をもとに、取引の詳細画面を表示できます。画面上のボタンで、売上取消・返品処理をおこなえます。ボタンは、`allowRefunding` パラメーターにNOを渡すことで、押せなくすることもできます。

下記の場合は、パラメーターにかかわらず、売上取消・返品ボタンが無効となります。ご注意ください。

* スタッフアカウントでログインしている（オーナー、マネージャーのみ取消できます）
* 既に売上取消・返品済み

また、60日以上経過している取引は、ボタンを押すとエラーとなり、取消できません。

### Objective-C

#### ViewController.m

```objective-c
#import "ViewController.h"
@import CoineyKit;

@interface ViewController () <CYCoineyViewControllerDelegate>
@end

@implementation ViewController

- (IBAction)makePayment:(id)aSender
{
    NSString *memo = _productNameField.text;
    NSInteger amount = [_productPriceField.text integerValue];

    // CYCoineyViewController のインスタンスを作成
    CYCoineyViewController * coineyController = [[CYCoineyViewController alloc] initWithAmount:amount memo:memo];
    coineyController.delegate = self;
    
    // ViewController の上に表示
    [self presentViewController:coineyController animated:YES completion:nil];
}

- (void)coineyViewController:(CYCoineyViewController *)aController
      didCompleteTransaction:(id<CYTransaction>)aTransaction
{
    NSLog(@"Completed transaction: %@", aTransaction);
    
    [aController dismissViewControllerAnimated:YES completion:^{
        CYTransactionViewController *transactionViewController =
            [CYTransactionViewController transactionViewControllerWithTransaction:aTransaction
                                                                   allowRefunding:YES];
                                                                   // 売上取消・返品不可にするには、NOを渡す
        transactionViewController.navigationItem.rightBarButtonItem =
            [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone
                                                          target:self
                                                          action:@selector(done:)];
        UINavigationController *navigationController =
            [[UINavigationController alloc] initWithRootViewController:transactionViewController];
        [navigationController setModalPresentationStyle:UIModalPresentationFormSheet];
        [self presentViewController:navigationController
                           animated:YES
                         completion:nil];
     }];
}

- (void)done:(id)aSender
{
	[self dismissViewControllerAnimated:YES completion:nil];
}
@end
```

### Swift

#### ViewController.swift

```swift
import UIKit
import CoineyKit

class ViewController: UIViewController {
    
    @IBOutlet weak var memoField: UITextField!
    @IBOutlet weak var amountField: UITextField!

    @IBAction func makePayment(sender: AnyObject) {
        let memo = productNameField.text ?? ""
        let amount = Int64(productPriceField.text!) ?? 0
        
       // CYCoineyViewController のインスタンスを作成
        guard let coineyController = CYCoineyViewController.init(amount: amount, memo: memo) else {
            fatalError("Failed to initialize CYCoineyViewController.")
        }
        coineyController.delegate = self
        
        // ViewController の上に表示
        self.present(coineyController, animated: true, completion: nil)
    }
    
    func done() {
    	self.dismiss(animated: true, completion: nil)
    }
}

extension ViewController : CYCoineyViewControllerDelegate {

    func coineyViewController(_ aController: CYCoineyViewController!,
                              didComplete aTransaction: CYTransaction!) {
        print("Completed transaction: \(aTransaction)")
        
        self.dismiss(animated: true, completion: {
            guard let transactionViewController =
                CYTransactionViewController.init(transaction: aTransaction, allowRefunding: true) else {
                    // 売上取消・返品不可にするには、allowRefunding: falseを渡す
                    fatalError("Failed to initialize CYTransactionViewController.")
            }
            
            transactionViewController.navigationItem.rightBarButtonItem =
                UIBarButtonItem.init(barButtonSystemItem: .done,
                                     target: self,
                                     action: #selector(self.done))
            
            let navigationController = UINavigationController.init(rootViewController: transactionViewController)
            navigationController.modalPresentationStyle = .formSheet
            self.present(navigationController, animated: true, completion: nil)
        })
    }
}
```

上記コードを実行すると、決済完了後、取引詳細が表示されます。

![App screenshot](.readme_images/simshot3.png)

## 取引履歴の参照

取引履歴から `CYTransaction` オブジェクトを取得するには、`CYLookUpTransaction()` を使います。

### Objective-C

```objective-c
CYLookUpTransaction(transactionIdentifier, ^(id<CYTransaction> transaction, NSError *err) {
    if(transaction)
        NSLog(@"Transaction found: %@", transaction);
        CYTransactionViewController *transactionViewController =
            [CYTransactionViewController transactionViewControllerWithTransaction:transaction
                                                                   allowRefunding:YES];
                                                                      
        transactionViewController.navigationItem.rightBarButtonItem =
            [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone   
                                                          target:self
                                                          action:@selector(done:)];
        UINavigationController *navigationController = [UINavigationController new];
        navigationController.viewControllers = @[transactionViewController];
        [navigationController setModalPresentationStyle:UIModalPresentationFormSheet];
        [self presentViewController:navigationController animated:YES completion:nil];
    }
    else
        NSLog(@"Transaction not found: %@", err);
});

...

- (void)done:(id)aSender
{
    [self dismissViewControllerAnimated:YES completion:nil];
}
```

### Swift

```swift
CYLookUpTransaction(transactionIdentifier, { aTransaction, aError in
    if let transaction = aTransaction {
        guard let transactionViewController =
            CYTransactionViewController.init(transaction: transaction, allowRefunding: true) else {
                fatalError("Failed to initialize CYTransactionViewController.")
        }
        
        transactionViewController.navigationItem.rightBarButtonItem =
            UIBarButtonItem.init(barButtonSystemItem: .done,
                                 target: self,
                                 action: #selector(self.done))
        
        let navigationController = UINavigationController.init(rootViewController: transactionViewController)
        navigationController.modalPresentationStyle = .formSheet
        self.present(navigationController, animated: true, completion: nil)
    } else if let error = aError {
        print("Transaction not found: \(error)")
    }
})

...

func done() {
    self.dismiss(animated: true, completion: nil)
}
```

ログイン済みでないと使用できませんので、ログイン状態が不明な場合は、以下のように`+[CTAuthenticationViewController CYCheckAuthenticationStatus:inViewController:]` でラップしてください。

```objective-c
[CYCheckAuthenticationStatus:^{
    CYLookUpTransaction(...
    ...
}
inViewController:viewController];
```

取得した`CYTransaction` オブジェクトを決済方法毎のオブジェクトにキャストして
より詳細な取引情報を参照することもできます。

### Objective-C

```objective-c
if ( [aTransaction conformsToProtocol:@protocol(CYCreditCardTransaction)] ) {
    id<CYCreditCardTransaction> cardTransaction = (id<CYCreditCardTransaction>)aTransaction;
    // クレジットカード決済
    NSLog(@"Credit Card%@", cardTransaction);
} else if ( [aTransaction conformsToProtocol:@protocol(CYWechatPayTransaction)] ) {
    id<CYWechatPayTransaction> wechatPayTransaction = (id<CYWechatPayTransaction>)aTransaction;
    // WeChatPay決済
    NSLog(@"WeChatPay %@", wechatPayTransaction);
}  else if ( [aTransaction conformsToProtocol:@protocol(CYEmoneyTransaction)] ) {
    id<CYEmoneyTransaction> emoneyTransaction = (id<CYEmoneyTransaction>)aTransaction;
    // 電子マネー決済
    NSLog(@"Emoney %@", emoneyTransaction);
}
```

### Swift

```swift
switch transaction {
case let creditCardTransaction as CYCreditCardTransaction:
    // クレジットカード決済
    print("\(creditCardTransaction)")
case let wechatPayTransaction as CYWechatPayTransaction:
    // WeChatPay決済
    print("\(wechatPayTransaction)")
case let emoneyTransaction as CYEmoneyTransaction:
    // 電子マネー決済
    print("\(emoneyTransaction)")
default:
    break
}
```

## レシート印刷

印刷機能をオンにすると、決済完了画面および取引詳細画面に [レシートを印刷] ボタンが表示され、レシートを印刷できます。デフォルトはオフです。

レシートを印刷するには:

1. アプリ起動時に `CYEnablePrinting(YES)` を呼びます。
2. アプにのInfo.plistに、以下のExternal Accessory Protocolsを追加します。

```xml
<key>UISupportedExternalAccessoryProtocols</key>
<array>
  <string>com.coiney.Coiney</string><!--コイニーターミナル-->
  <string>com.sii-ps.siieap</string>
  <string>com.epson.escpos</string>
  <string>jp.star-m.starpro</string>
</array>
```

3. iPadまたはiPhoneのBluetooth設定から、対応プリンターとペアリングします。対応機種はcoiney.comをご参照ください。

注1: 自社アプリでレシート印刷を実装する場合は、 `CYEnablePrinting(YES)` を呼ばないでください。 `EASession` をCoineyKitと共有できないためです。

## App Review への申請

Apple のアプリ審査を受けるにあたり、Coiney ターミナルの MFi 認証が必要になります。[こちら](../../wiki/PPID-の申請) のページをご覧ください。

## お問い合わせ

ご質問・ご要望等は、<coineykitsupport@coiney.com> までお問い合わせください。
