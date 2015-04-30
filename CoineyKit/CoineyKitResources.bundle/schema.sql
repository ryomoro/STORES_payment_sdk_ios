/*
 Navicat Premium Data Transfer

 Source Server         : Coiney mock
 Source Server Type    : SQLite
 Source Server Version : 3008004
 Source Database       : main

 Target Server Type    : SQLite
 Target Server Version : 3008004
 File Encoding         : utf-8

 Date: 10/14/2014 16:28:26 PM
*/

PRAGMA foreign_keys = false;

-- ----------------------------
--  Table structure for _dbkit_schemaInfo
-- ----------------------------
DROP TABLE IF EXISTS "_dbkit_schemaInfo";
CREATE TABLE "_dbkit_schemaInfo" (
    "version" integer NOT NULL
);

-- ----------------------------
--  Table structure for _lineItems_old_20141008
-- ----------------------------
DROP TABLE IF EXISTS "_lineItems_old_20141008";
CREATE TABLE "_lineItems_old_20141008" (
    "identifier" text NOT NULL,
    "unitPrice" integer DEFAULT 0,
    "quantity" integer DEFAULT 1,
    "transactionIdentifier" text,
    "productPriceIdentifier" text,
    "productName" text,
    "existsOnRemote" boolean,
    "memo" text,
    PRIMARY KEY("identifier"),
    FOREIGN KEY ("transactionIdentifier") REFERENCES "transactions" ("identifier") ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY ("productPriceIdentifier") REFERENCES "productPrices" ("identifier") ON DELETE SET NULL ON UPDATE CASCADE
);

-- ----------------------------
--  Table structure for _lineItems_old_20141008_1
-- ----------------------------
DROP TABLE IF EXISTS "_lineItems_old_20141008_1";
CREATE TABLE "_lineItems_old_20141008_1" (
    "identifier" TEXT NOT NULL,
    "unitPrice" integer DEFAULT 0,
    "quantity" integer DEFAULT 1,
    "transactionIdentifier" TEXT,
    "productPriceIdentifier" text,
    "productName" text,
    "existsOnRemote" boolean,
    "memo" text,
    PRIMARY KEY("identifier"),
    FOREIGN KEY ("transactionIdentifier") REFERENCES "transactions" ("identifier") ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY ("productPriceIdentifier") REFERENCES "productPrices" ("identifier") ON DELETE SET NULL ON UPDATE CASCADE
);

-- ----------------------------
--  Table structure for _shops_old_20141014
-- ----------------------------
DROP TABLE IF EXISTS "_shops_old_20141014";
CREATE TABLE "_shops_old_20141014" (
    "identifier" text NOT NULL,
    "name" text,
    "zipCode" text,
    "prefectureAndWard" text,
    "street" text,
    "streetNumber" text,
    "currencyCode" text,
    "revenueThisMonth" integer,
    "nextDepositDate" date,
    "depositLastClosedAt" date,
    "currentBalance" integer,
    "sandboxed" boolean,
    "manualCreditCardInputAllowed" boolean,
    "signlessTransactionsEnabled" boolean,
    "autoDepositEnabled" boolean,
    "locationRequired" boolean,
    "receiptAddress" text,
    "receiptPhoneNumber" text,
    "receiptEmail" text,
    "receiptURL" text,
    "receiptComment" text,
    PRIMARY KEY("identifier")
);

-- ----------------------------
--  Table structure for _transactions_old_20141008
-- ----------------------------
DROP TABLE IF EXISTS "_transactions_old_20141008";
CREATE TABLE "_transactions_old_20141008" (
    "identifier" text NOT NULL,
    "cardBrandName" text,
    "approvalCode" text,
    "cardSuffix" text,
    "latitude" real,
    "longitude" real,
    "amount" integer DEFAULT 0,
    "hasLocalChanges" boolean,
    "refunded" boolean,
    "chargeDate" date,
    "refundDate" date,
    "lastModificationDate" date,
    "createdOnThisDevice" boolean DEFAULT 0,
    "userFullName" text,
    "userEmail" text,
    "userIdentifier" text,
    "existsOnRemote" boolean,
    PRIMARY KEY("identifier")
);

-- ----------------------------
--  Table structure for _transactions_old_20141008_1
-- ----------------------------
DROP TABLE IF EXISTS "_transactions_old_20141008_1";
CREATE TABLE "_transactions_old_20141008_1" (
    "identifier" TEXT NOT NULL,
    "cardBrandName" text,
    "approvalCode" text,
    "cardSuffix" text,
    "latitude" real,
    "longitude" real,
    "amount" integer DEFAULT 0,
    "hasLocalChanges" boolean,
    "refunded" boolean,
    "chargeDate" date,
    "refundDate" date,
    "lastModificationDate" date,
    "createdOnThisDevice" boolean DEFAULT 0,
    "userFullName" text,
    "userEmail" text,
    "userIdentifier" text,
    "existsOnRemote" boolean,
    PRIMARY KEY("identifier")
);

-- ----------------------------
--  Table structure for deposits
-- ----------------------------
DROP TABLE IF EXISTS "deposits";
CREATE TABLE "deposits" (
    "identifier" text NOT NULL,
    "amount" integer,
    "status" integer,
    "date" date,
    "hasLocalChanges" boolean,
    "periodStart" date,
    "periodEnd" date,
    PRIMARY KEY("identifier")
);

-- ----------------------------
--  Table structure for lineItems
-- ----------------------------
DROP TABLE IF EXISTS "lineItems";
CREATE TABLE "lineItems" (
    "identifier" text NOT NULL,
    "unitPrice" integer DEFAULT 0,
    "quantity" integer DEFAULT 1,
    "transactionIdentifier" text,
    "productPriceIdentifier" text,
    "productName" text,
    "existsOnRemote" boolean,
    "memo" text,
    PRIMARY KEY("identifier"),
    FOREIGN KEY ("transactionIdentifier") REFERENCES "transactions" ("identifier") ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY ("productPriceIdentifier") REFERENCES "productPrices" ("identifier") ON DELETE SET NULL ON UPDATE CASCADE
);

-- ----------------------------
--  Table structure for productCategories
-- ----------------------------
DROP TABLE IF EXISTS "productCategories";
CREATE TABLE "productCategories" (
    "identifier" text NOT NULL,
    "name" text,
    "sortOrder" integer NOT NULL DEFAULT 0,
    "hasLocalChanges" boolean NOT NULL DEFAULT 0,
    "existsOnRemote" boolean,
    PRIMARY KEY("identifier")
);

-- ----------------------------
--  Table structure for productPrices
-- ----------------------------
DROP TABLE IF EXISTS "productPrices";
CREATE TABLE "productPrices" (
    "identifier" text NOT NULL,
    "name" text,
    "sortOrder" integer NOT NULL,
    "hasLocalChanges" boolean NOT NULL DEFAULT 0,
    "productIdentifier" text NOT NULL,
    "amount" integer NOT NULL,
    "existsOnRemote" boolean,
    PRIMARY KEY("identifier"),
    FOREIGN KEY ("productIdentifier") REFERENCES "products" ("identifier") ON DELETE CASCADE ON UPDATE CASCADE
);

-- ----------------------------
--  Table structure for products
-- ----------------------------
DROP TABLE IF EXISTS "products";
CREATE TABLE "products" (
    "identifier" text NOT NULL,
    "name" text,
    "sortOrder" integer NOT NULL DEFAULT 0,
    "hasLocalChanges" boolean NOT NULL DEFAULT 0,
    "categoryIdentifier" text,
    "existsOnRemote" boolean,
    PRIMARY KEY("identifier"),
    FOREIGN KEY ("categoryIdentifier") REFERENCES "productCategories" ("identifier") ON DELETE CASCADE ON UPDATE CASCADE
);

-- ----------------------------
--  Table structure for shops
-- ----------------------------
DROP TABLE IF EXISTS "shops";
CREATE TABLE "shops" (
    "identifier" text NOT NULL,
    "name" text,
    "zipCode" text,
    "prefectureAndWard" text,
    "street" text,
    "streetNumber" text,
    "phoneNumber" text,
    "currencyCode" text,
    "revenueThisMonth" integer,
    "nextDepositDate" date,
    "depositLastClosedAt" date,
    "currentBalance" integer,
    "industry" text,
    "placeOfUse" text,
    "url" text,
    "corporate" boolean,
    "sandboxed" boolean,
    "hasIndirectJCBContract" boolean,
    "paymentByInstallmentsAllowed" boolean,
    "manualCreditCardInputAllowed" boolean,
    "signlessTransactionsAllowed" boolean,
    "signlessTransactionsEnabled" boolean,
    "autoDepositEnabled" boolean,
    "minimumDepositAmount" integer,
    "locationRequired" boolean,
    "acceptedCardBrands" integer,
    "receiptShopName" text,
    "receiptAddress" text,
    "receiptPhoneNumber" text,
    "receiptEmail" text,
    "receiptURL" text,
    "receiptComment" text,
    "signlessTransactionCeiling" integer,
    "companyName" text,
    "companyZipCode" text,
    "companyCity" text,
    "companyStreet" text,
    "companyPhoneNumber" text,
    "accountHolderFirstName" text,
    "accountHolderLastName" text,
    "accountHolderZipCode" text,
    "accountHolderCity" text,
    "accountHolderStreet" text,
    "accountHolderPhoneNumber" text,
    "accountHolderBirthDate" date,
    "accountHolderGender" text,
    "bankName" text,
    "bankBranchName" text,
    "bankAccountType" text,
    "bankAccountNumber" text,
    "nameOnBankAccount" text,
    PRIMARY KEY("identifier")
);

-- ----------------------------
--  Table structure for transactions
-- ----------------------------
DROP TABLE IF EXISTS "transactions";
CREATE TABLE "transactions" (
    "identifier" text NOT NULL,
    "cardBrandName" text,
    "approvalCode" text,
    "cardSuffix" text,
    "latitude" real,
    "longitude" real,
    "amount" integer DEFAULT 0,
    "financing" integer DEFAULT 0,
    "hasLocalChanges" boolean,
    "refunded" boolean,
    "chargeDate" date,
    "refundDate" date,
    "updatedAt" date,
    "createdOnThisDevice" boolean DEFAULT 0,
    "userFullName" text,
    "userEmail" text,
    "userIdentifier" text,
    "existsOnRemote" boolean,
    PRIMARY KEY("identifier")
);

-- ----------------------------
--  Table structure for users
-- ----------------------------
DROP TABLE IF EXISTS "users";
CREATE TABLE "users" (
    "identifier" text NOT NULL,
    "fullName" text,
    "email" text,
    "joinedAt" date,
    "roleString" text,
    "suspended" boolean,
    "hasLocalChanges" boolean,
    PRIMARY KEY("identifier")
);

-- ----------------------------
--  Table structure for contracts
-- ----------------------------
DROP TABLE IF EXISTS "contracts";
CREATE TABLE "contracts" (
    "identifier" text NOT NULL,
    "authority" integer,
    "establishedBy" text,
    PRIMARY KEY("identifier")
);

-- ----------------------------
--  View structure for categoryItems
-- ----------------------------
DROP VIEW IF EXISTS "categoryItems";
CREATE VIEW "categoryItems" AS SELECT identifier, name, sortOrder, categoryIdentifier, 0 as isCategory, 0 AS childCount FROM products ORDER BY sortOrder ASC;

-- ----------------------------
--  View structure for inventoryItems
-- ----------------------------
DROP VIEW IF EXISTS "inventoryItems";
CREATE VIEW "inventoryItems" AS SELECT * FROM (
    SELECT identifier,
           name, 
           sortOrder,
           NULL AS categoryIdentifier,
           1 AS isCategory, 
           (SELECT COUNT(*) FROM products WHERE products.categoryIdentifier = productCategories.identifier) AS childCount,
           (SELECT group_concat(identifier) FROM (SELECT identifier FROM products  WHERE products.categoryIdentifier = productCategories.identifier ORDER BY products.sortOrder ASC LIMIT 4)) AS thumbnailIdentifiers
    FROM productCategories
UNION
    SELECT identifier, 
           name,
           sortOrder,
           categoryIdentifier, 
           0 as isCategory, 
           0 AS childCount,
           identifier AS thumbnailIdentifiers 
    FROM products
) ORDER BY sortOrder ASC;

-- ----------------------------
--  View structure for sortOrder
-- ----------------------------
DROP VIEW IF EXISTS "sortOrder";
CREATE VIEW "sortOrder" AS SELECT sortOrder, categoryIdentifier FROM products
UNION
SELECT sortOrder, NULL AS categoryIdentifier FROM productCategories;

-- ----------------------------
--  View structure for transactionAmountThisMonth
-- ----------------------------
DROP VIEW IF EXISTS "transactionAmountThisMonth";
CREATE VIEW "transactionAmountThisMonth" AS
SELECT SUM(subtotal) AS total FROM
(
    SELECT 'charges' AS description, SUM(amount) AS subtotal FROM transactions
        WHERE chargeDate NOT NULL AND strftime('%Y-%m', chargeDate) = strftime('%Y-%m', 'now')
    UNION
    SELECT 'refunds' AS description, SUM(amount * -1) AS subtotal FROM transactions
        WHERE refundDate NOT NULL AND strftime('%Y-%m', refundDate) = strftime('%Y-%m', 'now')
);

-- ----------------------------
--  Indexes structure for table lineItems
-- ----------------------------
CREATE INDEX "memo" ON lineItems ("memo" ASC);

-- ----------------------------
--  Indexes structure for table transactions
-- ----------------------------
CREATE INDEX "search" ON transactions ("amount" ASC, "cardSuffix" ASC);

-- ----------------------------
--  Indexes structure for table users
-- ----------------------------
CREATE INDEX "sort" ON users (identifier COLLATE BINARY ASC);

-- ----------------------------
--  Triggers structure for view sortOrder
-- ----------------------------
CREATE TRIGGER "updateSortOrder"
 INSTEAD OF UPDATE ON sortOrder
FOR EACH ROW
WHEN OLD.sortOrder != NEW.sortOrder AND OLD.categoryIdentifier = NEW.categoryIdentifier
BEGIN
    UPDATE products
        SET sortOrder = NEW.sortOrder 
        WHERE sortOrder = OLD.sortOrder AND products.categoryIdentifier = OLD.categoryIdentifier;
    UPDATE productCategories 
        SET sortOrder = (CASE WHEN OLD.categoryIdentfier IS NULL THEN NEW.sortOrder ELSE productCategories.sortOrder END) 
        WHERE sortOrder = OLD.sortOrder;
END;

PRAGMA foreign_keys = true;
