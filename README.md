# CoineyKit

CoineyKit をご利用いただき、ありがとうございます。ご要望やバグ報告の際は、お手数ですが [GitHub issue](https://github.com/Coiney/CoineyKit-iOS/issues) を作成いただきますようお願い致します。

-------

# サンプルアプリ

## 目的

このチュートリアルでは、CoineyKitを使って、カード決済ができるサンプルアプリを作成します。

(完成したものが、`Example/Coiney Test.xcodeproj` にあります)

## 必要なもの

 * CoineyKit (このレポジトリを `git clone`、または .zip 形式でダウンロードしてください)
 * Xcode 7 以上
 

## プロジェクトのセットアップ

Xcode を起動し、`File → New → Project` から、`Single View Application` を選択します。

![Template selection](.readme_images/template-selection.png)

下記のように設定します。

![Template options](.readme_images/template-options.png)

本レポジトリを `git clone` またはダウンロードし、`CoineyKit` フォルダを、`«プロジェクトフォルダ»/CoineyKit` となるように、プロジェクトフォルダの中へコピーします。

![Folder hierarchy](.readme_images/folder-hierarchy.png)

Git をお使いでしたら、更新しやすいように、submodule として追加することをお勧めします。

`CoineyKit.xcconfig` と `CoineyKitResources.bundle` を、Xcode のプロジェクトナビゲーターにドラッグ＆ドロップします。

次に、Debug・Release 両方の configuration に "CoineyKit" を指定してください。

![Configurations](.readme_images/configuration.png)

ターゲットの General 設定を開き、`CoineyKit.framework` および下記ライブラリをリンクするようにします。

 * libxml2.tbd
 * libsqlite3.tbd

![Libraries and Frameworks](.readme_images/frameworks-libs.png)

もう少しでセットアップは完了です。

#### Info.plist への追加

Bluetooth で Coiney ターミナルに接続し、IC や磁気カード決済をするために、`UISupportedExternalAccessoryProtocols` を追加する必要があります。

```
<key>UISupportedExternalAccessoryProtocols</key>
<array>
  <string>com.coiney.Coiney</string>
</array>
```

iOS 9 の App Transport Security に対応するために、`NSAppTransportSecurity` を追加してください。

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

今後すべてのリンクを https にしていくため、将来的に不要になる予定です。http で取得しているのは、利用規約などの静的ページのみです。決済に携わる通信には https を使っておりますので、安心してご利用いただけます。

## 決済をする

### Objective-C

`ViewController.h` と `ViewController.m` を開き、下記のコードを貼り付けてください。

#### ViewController.h

    #import <UIKit/UIKit.h>
    
    @interface ViewController : UIViewController
    @property(weak, nonatomic) IBOutlet UITextField *productMemoField, *productPriceField;
    
    - (IBAction)makePayment:(id)aSender;
    @end

#### ViewController.m

    #import "ViewController.h"
    @import CoineyKit;

    @implementation ViewController

    - (IBAction)makePayment:(id)aSender
    {
        // CYCoineyController に渡す CYItem を作成
        NSString *memo = _productMemoField.text;
        int price = [_productPriceField.text intValue];
    
        CYItem *item = [CYItem itemWithTotal:price
                                    currency:CYCurrencyJPY
                                        memo:memo];
    
        // CYCoineyViewController のインスタンスを作成
        CYCoineyViewController * coineyController = [[CYCoineyViewController alloc] initWithLineItems:@[item]];
    
        // ViewController の上に表示
        [self presentViewController:coineyController animated:YES completion:nil];
    }
    @end
    
### Swift

#### ViewController.swift

    import UIKit
    import CoineyKit
    
    class ViewController: UIViewController {
        @IBOutlet var memoField: UITextField?
        @IBOutlet var amountField: UITextField?
        
        @IBAction func makePayment(sender: AnyObject) {
            let amount: UInt? = amountField == nil ? nil : UInt(amountField!.text!)
            if (amount != nil) {
                let item: CYItem = CYItem(total: amount!, currency: .JPY, memo: memoField?.text)
                let coineyController: CYCoineyViewController = CYCoineyViewController(lineItems: [item])
                self.presentViewController(coineyController, animated: true, completion: nil)
            }
        }
    }
    
`Main.storyboard` でボタンを作り、押されたら `makePayment:` が呼び出されるようにしてください。`productNameField` と `productPriceField` はそれぞれ `IBOutlet` をフィールドにつなげてください。

![Action connection](.readme_images/action-connection.png)

iPhone で実行すると、下記のようになります。

![App screenshot](.readme_images/simshot1.png)

あとはターミナルかリーダーを繋げば決済できます。ターミナルへ接続するには、「ターミナルに接続する」をタップし、説明に従ってください。

## 結果の通知を受け取る

### Objective-C

デリゲートメソッドを使って、決済完了時とキャンセル時に通知を受け取ることができます。下記のように、`ViewController.m` に `CYCoineyViewControllerDelegate` プロトコルを実装させ、`coineyViewController:didCompleteTransaction:` および `coineyViewControllerDidCancel:` を実装してください。

#### ViewController.m

    #import "ViewController.h"
    @import CoineyKit;
    
    @interface ViewController () <CYCoineyViewControllerDelegate>
    @end
    
    @implementation ViewController
    
    - (IBAction)makePayment:(id)aSender
    {
        // Create a line item to pre-populate the Coiney controller with.
        NSString *memo = _productMemoField.text;
        NSInteger price = [_productPriceField.text integerValue];
        
        CYItem *item = [CYItem itemWithTotal:price
                                    currency:CYCurrencyJPY
                                        memo:memo];
        
        // Create an instance of the Coiney payment controller.
        CYCoineyViewController * coineyController = [[CYCoineyViewController alloc] initWithLineItems:@[item]];
        coineyController.delegate = self;
        // Present it on top of the current controller.
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
        NSLog(@"Cancelled");
    }
    @end
    
### Swift

#### ViewController.swift

    import UIKit
    import CoineyKit

    class ViewController: UIViewController, CYCoineyViewControllerDelegate {
        @IBOutlet var memoField: UITextField?
        @IBOutlet var amountField: UITextField?
    
        @IBAction func makePayment(sender: AnyObject) {
            let amount: UInt? = amountField == nil ? nil : UInt(amountField!.text!)
            if (amount != nil) {
                let item: CYItem = CYItem(total: amount!, currency: .JPY, memo: memoField?.text)
                let coineyController: CYCoineyViewController = CYCoineyViewController(lineItems: [item])
                coineyController.delegate = self
                self.presentViewController(coineyController, animated: true, completion: nil)
            }
        }
    
        func coineyViewController(aController: CYCoineyViewController!,
             didCompleteTransaction aTransaction: CYTransaction!) {
            print("Completed transaction: \(aTransaction)")
        }
    
        func coineyViewControllerDidCancel(aController: CYCoineyViewController!) {
            self.dismissViewControllerAnimated(true, completion: nil)
            print("Cancelled")
        }
    }
    
## 取引詳細の表示・売上取消

取引 ID をもとに、取引の詳細画面を表示できます。詳細画面上の売上取消・返品ボタンより、売上取消・返品をおこなえます。売上取消・返品ボタンは、パラメータにより、非表示にすることもできます。

下記の場合は売上取消・返品ボタンが表示されませんので、ご注意ください。

* `allowRefunding:NO` を渡した
* スタッフアカウントでログインしている（オーナー、マネージャーのみ売上取消できます）
* 取引日から61日以上経過している
* 既に売上取消済み

### Objective-C

#### ViewController.m

    #import "ViewController.h"
    @import CoineyKit;
    
    @interface ViewController () <CYCoineyViewControllerDelegate>
    @end
    
    @implementation ViewController
    
    - (IBAction)makePayment:(id)aSender
    {
        NSString *memo = _productMemoField.text;
        int price = [_productPriceField.text intValue];
        
        CYItem *item = [CYItem itemWithTotal:price
                                        currency:CYCurrencyJPY
                                            memo:memo];
        CYCoineyViewController * coineyController = [[CYCoineyViewController alloc] initWithLineItems:@[item]];
        coineyController.delegate = self;
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
                                                              // 売上取消・返品ボタンを非表示にするには、NO を渡してください
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
    
### Swift

#### ViewController.swift

    import UIKit
    import CoineyKit

    class ViewController: UIViewController, CYCoineyViewControllerDelegate {
        @IBOutlet var memoField: UITextField?
        @IBOutlet var amountField: UITextField?
    
        @IBAction func makePayment(sender: AnyObject) {
            let amount: UInt? = amountField == nil ? nil : UInt(amountField!.text!)
            if (amount != nil) {
                let item: CYItem = CYItem(total: amount!, currency: .JPY, memo: memoField?.text)
                let coineyController: CYCoineyViewController = CYCoineyViewController(lineItems: [item])
                coineyController.delegate = self
                self.presentViewController(coineyController, animated: true, completion: nil)
            }
        }
    
        func coineyViewController(aController: CYCoineyViewController!,
            didCompleteTransaction aTransaction: CYTransaction!) {                                
            self.dismissViewControllerAnimated(true) { () -> Void in
                let transactionController = CYTransactionViewController(transaction: aTransaction,
                    allowRefunding: true)
                transactionController.navigationItem.rightBarButtonItem =
                    UIBarButtonItem(barButtonSystemItem: .Done, target: self, action: "done")
                let navigationController = UINavigationController(rootViewController: transactionController)
                navigationController.modalPresentationStyle = .FormSheet
                self.presentViewController(navigationController, animated: true, completion: nil)
            }
        }
    
        func done() {
            self.dismissViewControllerAnimated(true, completion: nil)
        }
    }

上記コードを実行すると、決済完了後、取引詳細が表示されます。

![App screenshot](.readme_images/simshot3.png)

## 取引履歴の参照

取引履歴から `CYTransaction` オブジェクトを取得するには、`CYLookUpTransaction()` を使います。

### Objective-C

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
    
### Swift

    CYLookUpTransaction(transactionIdentifier, { (transaction, error) -> Void in
        if error != nil {
            print("Transaction not found: \(error)")
        } else {
            let transactionController = CYTransactionViewController(transaction: transaction, allowRefunding: true)
            transactionController.navigationItem.rightBarButtonItem =
                UIBarButtonItem(barButtonSystemItem: .Done, target: self, action: "done")
            let navigationController = UINavigationController(rootViewController: transactionController)
            navigationController.modalPresentationStyle = .FormSheet
            self.presentViewController(navigationController, animated: true, completion: nil)
        }
    })
    
    ...
    
    func done() {
        self.dismissViewControllerAnimated(true, completion: nil)
    }

## レシート印刷

_注: 当機能は提供終了予定のため、使用を推奨しておりません。レシート印刷は POS アプリ側で実装いただきますようお願い致します。_

レシートを印刷するには、決済完了画面・取引詳細画面のプリントボタンを押すか、CoineyKit のプリント API を使用します。

CoineyKit でレシート印刷を可能にするには、最初に `+[CYPrinter setPrintingEnabled:YES]` を呼んでください。

#### AppDelegate.m

    - (void)applicationDidFinishLaunching:(UIApplication *)aApplication
    {
        [CYPrinter setPrintingEnabled:YES];
    }

印字内容は [ReceiptML](/Documentation/ReceiptML) というフォーマットで記述します。

下記のサンプルコードでは、決済完了後にレシートを印刷します。

#### ViewController.m
    
    #import "ViewController.h"
    @import CoineyKit;
    
    @implementation ViewController
    
    - (IBAction)makePayment:(id)aSender
    {
        CYCoineyViewController * const coineyController = [CYCoineyViewController new];
        [self presentViewController:coineyController animated:YES completion:nil];
    }
    
    - (void)coineyViewController:(CYCoineyViewController *)aController
          didCompleteTransaction:(id<CYTransaction>)aTransaction
    {
        NSLog(@"Completed transaction: %@", aTransaction);
    
        NSMutableString * const ml = [NSMutableString stringWithString:
                                      @"<receipt>\n"
                                      @"<title font-name=\"HiraKakuProN-W6\">Coiney Store</title>\n"
                                      @"<subtitle>123-456-7890</subtitle>\n"];
        [ml appendString:[NSString stringWithFormat:
                         @"<subtitle>%@</subtitle>\n", [NSDate date]]];
        [ml appendString:@"<ruler/>\n"
                         @"<line-item>\n"
                         @"\t<name>Item A</name>\n"];
        [ml appendString:[NSString stringWithFormat:
                         @"\t<price>%d</price>\n", [aTransaction.amount intValue]]];
        [ml appendString:@"</line-item>\n"
                         @"<total/>\n"
                         @"<ruler/>\n"];
        [ml appendString:[NSString stringWithFormat:
                         @"<subtitle font-size=\"17\">%@ %@</subtitle>\n",
                         NSStringFromCYCardbrand(aTransaction.cardBrand),
                         aTransaction.cardSuffix]];
        [ml appendString:@"</receipt>\n"];
    
        if([[CYPrinter connectedPrinters] count] == 0)
            NSLog(@"No connected printers");
        else {
            // Print
            for (CYPrinter * printer in [CYPrinter connectedPrinters]) {
                [printer batchPrint:^{
                    [printer printReceiptML:ml];
                } cutWhenDone:YES];
            }
        }
    }

対応プリンタ:

スター精密

* SM-S210i
* TSP650II

エプソン

* TM-P60II
* TM-T20II
* TM−m10

App Review へ申請する際は、下記キーを Info.plist に追加し、プリンターメーカーに MFi 認証してもらう必要があります。詳しくは [MFi Program](https://developer.apple.com/programs/mfi/) をご覧ください。

	<key>UISupportedExternalAccessoryProtocols</key>
	<array>
		<string>jp.star-m.starpro</string>
		<string>com.epson.escpos</string>
	</array>

独自実装でレシート印刷する場合には、必ず `[CYPrinter setPrintingEnabled:NO]` としてください。

## App Review への申請

Apple のアプリ審査を受けるにあたり、Coiney ターミナルの MFi 認証が必要になります。[こちら](../../wiki/PPID-の申請) のページをご覧ください。

## お問い合わせ

ご質問・ご要望等は、<coineykit-support@coiney.com> までお問い合わせください。
