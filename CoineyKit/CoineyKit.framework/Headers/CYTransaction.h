// CoineyKit
// Copyright © Coiney Inc. All rights reserved.
// For licensing information, contact info@coiney.com.

#import <CoreData/CoreData.h>
#import <CoineyKit/CYTypes.h>

/// \~english
/// Represents a transaction made through Coiney.
///
/// **Warning** Do not attempt to pass custom `CYTransaction` conforming classes to CoineyKit.
/// \~japanese
/// 一つの決済を表します。
///
/// **注** `CYTransaction` プロトコルを適用したカスタムクラスを CoineyKit に渡さないこと。
@protocol CYTransaction <NSObject>

/// \~english
/// A unique transaction identifier
/// \~japanese
/// 決済の一意なID
@property(nonatomic, readonly) NSString *identifier;
/// \~english
/// A representation of the identifier for displaying to users.
/// (Not guaranteed to be unique)
/// \~japanese
/// `identifier` をユーザーに表示するためにフォーマットした値
/// (一意であるとは限りません)
@property(nonatomic, readonly) NSString *humanReadableIdentifier;
/// \~english
/// Returns the date/time of the transaction
/// \~japanese
/// 決済の日時
@property(nonatomic, readonly) NSDate *chargeDate;
/// \~english
/// Returns the date/time of the refund, or nil if not refunded.
/// \~japanese
/// 返品の日時（未返品であればnil）
@property(nonatomic, readonly) NSDate *refundDate;
/// \~english
/// The amount of the transaction in Japanese Yen
/// \~japanese
/// 決済額 (日本円)
@property(nonatomic, nonatomic, readonly) int64_t amount;
/// \~english
/// The brand of credit card used to make the transaction
/// \~japanese
/// 決済に使われたカードブランド
@property(nonatomic, readonly) CYCardBrand cardBrand;
/// \~english
/// Returns a string containing the last 4 digits of the credit card's number
/// \~japanese
/// カード番号の下4桁
@property(nonatomic, readonly) NSString *cardSuffix;
/// \~english
/// Method of credit card financing (installments, revolving, etc.)
/// \~japanese
/// 支払区分
@property(nonatomic, readonly) CYFinancingType financing;
/// \~english
/// Returns whether or not the transaction has been refunded
/// \~japanese
/// 返品済みかどうか
@property(nonatomic, readonly, getter=isRefunded) BOOL refunded;
/// \~english
/// Returns the approval code from the acquirer
/// \~japanese
/// アクワイアラが発行する承認コード
@property(nonatomic, strong) NSString *approvalCode;
/// \~english
/// Returns the AID for an IC card transaction
/// \~japanese
/// IC カード決済の AID
@property(nonatomic, strong) NSString *applicationIdentifier;
/// \~english
/// Returns the application label for an IC card transaction
/// \~japanese
/// IC カード決済のアプリケーションラベル
@property(nonatomic, strong) NSString *applicationLabel;

/// \~english
/// Generates a bitmap for the transaction's receipt.
/// \param aWidth The width of the `UIImage` to be returned
/// \return The transaction's receipt rendered as a `UIImage`
/// \~japanese
/// 決済のレシートをビットマップとして描画します。
/// \param aWidth 生成する `UIImage` の幅
/// \return 描画した `UIImage`
- (UIImage *)receiptImageWithWidth:(float const)aWidth;

/// \~english
/// Generates a ReceiptML string with the transaction data.
/// \return The transaction data in ReceiptML format.
/// \~japanese
/// 決済データを ReceiptML 形式で返します。
/// \return ReceiptML 形式の決済データ
- (NSString *)receipt;
@end

/// \~english
/// A block object type for doing something with a looked up transaction.
/// Parameters are: the relevant transaction, or an error in case lookup failed.
/// \~japanese
/// `CYLookUpTransaction()` で参照した決済に対して、処理を行うためのブロック型です。
/// パラメータには、該当する決済オブジェクトか、参照に失敗した場合はエラーが渡されます。
typedef void (^CYTransactionLookupBlock)(id<CYTransaction> aTransaction, NSError *aError);

/// \~english
/// Queries Coiney for a given transaction identifier and if found, passes it to the completion block.
/// If none is found nil is passed for the transaction.
/// \param aIdentifier The identifier of the transaction to look up
/// \param aCompletionBlock A block to be executed upon completion
/// \~japanese
/// 渡したIDを元に決済を参照し、ブロックを実行します。
/// 一致するものあれば `CYTransaction` オブジェクトを、なければ `nil` をブロックに渡します。
/// \param aIdentifier 参照する決済ID
/// \param aCompletionBlock 参照後に実行するブロック
void CYLookUpTransaction(NSString *aIdentifier, CYTransactionLookupBlock aCompletionBlock);

/// \~english
/// Minimum and maximum transaction amounts.
/// \~japanese
/// 決済の最低額 (¥100) と最高額 (¥9,999,999)
extern const NSUInteger kCYMinAmount, kCYMaxAmount;
