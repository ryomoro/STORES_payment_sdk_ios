// CoineyKit
// Copyright © Coiney Inc. All rights reserved.
// For licensing information, contact info@coiney.com.

#import <UIKit/UIKit.h>

/// \~english
/// Block signature for checking authentication status.
/// \~japanese
/// ログイン状態のチェックに使うブロック型です。
typedef void (^CYAuthenticationStatusBlock)(BOOL aIsAuthenticated);

/// \~english
/// `CYAuthenticationViewController` allows a user to log in to Coiney.
/// \~japanese
/// ログイン画面のビューコントローラです。
@interface CYAuthenticationViewController : UIViewController

/// \~english
/// Checks the authentication status of CoineyKit and notifies `aCompletionBlock`
/// if `aParentViewController` is provided, a login dialog will be presented on top of it
/// in the case where the user is not currently logged in.
/// \param aCompletionBlock The block to execute upon completion
/// \param aParentViewController Parent of login dialog
/// \~japanese
/// CoineyKit のログイン状態をチェックし、必要に応じてログイン画面を表示後、 終了ブロックを実行します。
/// `aParentViewController` が `nil` でなく、且つ未ログインなら、ログイン画面を表示します。
/// \param aCompletionBlock 終了時に実行するブロック
/// \param aParentViewController 未ログイン状態なら、この上にログイン画面を表示
+ (void)checkAuthenticationStatus:(CYAuthenticationStatusBlock _Nullable)aCompletionBlock
                 inViewController:(UIViewController * _Nullable)aParentViewController;

/// \~english
/// Deletes any stored credentials, so the user is required to log in the next time a
/// `CYCoineyViewController` is shown.
/// \~japanese
/// 保持されているログイン情報をクリアします。
+ (void)deauthenticate;

@end

/// \~english
/// Text for pre-populating the username field.
/// \~japanese
/// `CYAuthenticationViewController` 表示時に、メールアドレス欄に予め記入する文字列
extern NSString * _Nullable CYAuthenticationControllerDefaultEmail;

/// \~english
/// Text for pre-populating the password field.
/// \~japanese
/// `CYAuthenticationViewController` 表示時に、パスワード欄に予め記入する文字列
extern NSString * _Nullable CYAuthenticationControllerDefaultPassword;
