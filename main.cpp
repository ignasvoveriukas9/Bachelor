#include <algorithm>
#include <cstdio>
#include <ctime>
#include <cwchar>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "ADXCalculator.h"
#include "Agent.h"
#include "DbFiller.h"
#include "DbManager.h"
#include "GlobalTrendAnalyzer.h"
#include "InventoryManager.h"
#include "Price.h"
#include "PriceDataProvider.h"

int main() {
  /*DbManager dbManager;

  Agent agentSOL3Long = Agent(
      1, 0.03, 1, 0.1, "../rez/SOL/3percent/byBitSOLUSDTLongSellLogDRAL.csv",
      "../rez/SOL/3percent/byBitSOLUSDTLongBuyLogtrs.csv");

  Agent agentSOL3Short = Agent(
      -1, 0.03, 1, 0.1, "../rez/SOL/3percent/byBitSOLUSDTShortSellLogDRAL.csv",
      "../rez/SOL/3percent/byBitSOLUSDTShortBuyLogtrs.csv");

  std::vector<Price> priceList = dbManager.getPrices(
      "test.db", "byBit_SOLUSDT", 1715011199999, 1717344000001);

  for (int i = 0; i < priceList.size(); ++i) {
    agentSOL3Long.run(priceList [ i ]);
    // agentSOL3Short.run(priceList [ i ]);
  }*/

  /*ADXCalculator adx = ADXCalculator(14);

  std::vector<PriceData> sampleData = {
      {44.53, 43.98, 44.52}, {44.93, 44.36, 44.65}, {45.39, 44.70, 45.22},
      {45.70, 45.13, 45.45}, {45.63, 44.89, 45.49}, {45.52, 44.20, 44.24},
      {44.71, 44.00, 44.62}, {45.15, 43.76, 45.15}, {45.65, 44.46, 44.54},
      {45.87, 45.13, 45.66}, {45.99, 45.27, 45.95}, {46.35, 45.80, 46.33},
      {46.61, 46.10, 46.31}, {46.47, 45.77, 45.94}, {46.30, 45.14, 45.60},
      {45.98, 44.97, 45.70}, {46.68, 46.10, 46.56}, {46.59, 46.14, 46.36},
      {46.88, 46.39, 46.83}, {46.81, 46.41, 46.72}, {46.74, 45.94, 46.65},
      {47.08, 46.68, 46.97}, {46.84, 46.17, 46.56}, {45.81, 45.10, 45.29},
      {45.13, 44.35, 44.94}, {44.96, 44.61, 44.62}, {45.01, 44.20, 44.70},
      {45.67, 44.93, 45.27}, {45.71, 45.01, 45.44}, {45.35, 44.46, 44.76}};

  for (const auto& data : sampleData) {
    // adx.addPriceData(data);
    double currentADX = adx.calculateADX(data);
    std::cout << "currentADX: " << currentADX << std::endl;
  }*/
  // double currentADX = adx.calculateADX();
  // std::cout << "currentADX: " << currentADX << std::endl;
  //

  PriceDataProvider dp;
  GlobalTrendAnalyzer globalTrendAnalyzer;

  Agent agentBTCLong = Agent(1, 0.02, 10, 0.15,
                             "../rez/BTC/Original/2perc/BTCUSDTLongSellLog.csv",
                             "../rez/BTC/Original/2perc/BTCUSDTLongBuyLog.csv");
  Agent agentBTCShort = Agent(
      -1, 0.02, 10, 0.15, "../rez/BTC/Original/2perc/BTCUSDTShortSellLog.csv",
      "../rez/BTC/Original/2perc/BTCUSDTShortBuyLog.csv");
  std::vector<Price> priceListBTC =
      dp.getPrices("../data/BTCUSDT.csv", "BTCUSDT", 1600756200, 1746218400);
  globalTrendAnalyzer.addPair("BTCUSDT",
                              "../rez/BTC/Original/2perc/BTCUSDTADXLog.csv");
  double BTCCashAvailable = 0.0;
  std::string BTCValueLog = "../rez/BTC/Original/2perc/BTCValueLog.csv";

  Agent agentETHLong = Agent(1, 0.02, 10, 0.15,
                             "../rez/ETH/Original/2perc/ETHUSDTLongSellLog.csv",
                             "../rez/ETH/Original/2perc/ETHUSDTLongBuyLog.csv");
  Agent agentETHShort =
      Agent(-1, 0.02, 10, 0.15,
            "../rez/ETH/Original/2perc/ETHUSDTShortSellLogDSL.csv",
            "../rez/ETH/Original/2perc/ETHUSDTShortBuyLogDSL.csv");
  std::vector<Price> priceListETH =
      dp.getPrices("../data/ETHUSDT.csv", "ETHUSDT", 1600756200, 1746218400);
  globalTrendAnalyzer.addPair("ETHUSDT",
                              "../rez/ETH/Original/2perc/ETHUSDTADXLog.csv");
  double ETHCashAvailable = 0.0;
  std::string ETHValueLog = "../rez/ETH/Original/2perc/ETHValueLog.csv";

  Agent agentSOLLong = Agent(1, 0.02, 10, 0.15,
                             "../rez/SOL/Original/2perc/SOLUSDTLongSellLog.csv",
                             "../rez/SOL/Original/2perc/SOLUSDTLongBuyLog.csv");
  Agent agentSOLShort = Agent(
      -1, 0.02, 10, 0.15, "../rez/SOL/Original/2perc/SOLUSDTShortSellLog.csv",
      "../rez/SOL/Original/2perc/SOLUSDTShortBuyLog.csv");
  std::vector<Price> priceListSOL =
      dp.getPrices("../data/SOLUSDT.csv", "SOLUSDT", 1600756200, 1746218400);
  globalTrendAnalyzer.addPair("SOLUSDT",
                              "../rez/SOL/Original/2perc/SOLUSDTADXLog.csv");
  double SOLCashAvailable = 0.0;
  std::string SOLValueLog = "../rez/SOL/Original/2perc/SOLValueLog.csv";

  Agent agentXRPLong = Agent(1, 0.02, 10, 0.15,
                             "../rez/XRP/Original/2perc/XRPUSDTLongSellLog.csv",
                             "../rez/XRP/Original/2perc/XRPUSDTLongBuyLog.csv");
  Agent agentXRPShort = Agent(
      -1, 0.02, 10, 0.15, "../rez/XRP/Original/2perc/XRPUSDTShortSellLog.csv",
      "../rez/XRP/Original/2perc/XRPUSDTShortBuyLog.csv");
  std::vector<Price> priceListXRP =
      dp.getPrices("../data/XRPUSDT.csv", "XRPUSDT", 1600756200, 1746218400);
  globalTrendAnalyzer.addPair("XRPUSDT",
                              "../rez/XRP/Original/2perc/XRPUSDTADXLog.csv");
  double XRPCashAvailable = 0.0;
  std::string XRPValueLog = "../rez/XRP/Original/2perc/XRPValueLog.csv";

  Agent agentADALong = Agent(1, 0.02, 10, 0.15,
                             "../rez/ADA/Original/2perc/ADAUSDTLongSellLog.csv",
                             "../rez/ADA/Original/2perc/ADAUSDTLongBuyLog.csv");
  Agent agentADAShort = Agent(
      -1, 0.02, 10, 0.15, "../rez/ADA/Original/2perc/ADAUSDTShortSellLog.csv",
      "../rez/ADA/Original/2perc/ADAUSDTShortBuyLog.csv");
  std::vector<Price> priceListADA =
      dp.getPrices("../data/ADAUSDT.csv", "ADAUSDT", 1600756200, 1746218400);
  globalTrendAnalyzer.addPair("ADAUSDT",
                              "../rez/ADA/Original/2perc/ADAUSDTADXLog.csv");
  double ADACashAvailable = 0.0;
  std::string ADAValueLog = "../rez/ADA/Original/2perc/ADAValueLog.csv";

  Agent agentBNBLong = Agent(1, 0.02, 10, 0.15,
                             "../rez/BNB/Original/2perc/BNBUSDTLongSellLog.csv",
                             "../rez/BNB/Original/2perc/BNBUSDTLongBuyLog.csv");
  Agent agentBNBShort = Agent(
      -1, 0.02, 10, 0.15, "../rez/BNB/Original/2perc/BNBUSDTShortSellLog.csv",
      "../rez/BNB/Original/2perc/BNBUSDTShortBuyLog.csv");
  std::vector<Price> priceListBNB =
      dp.getPrices("../data/BNBUSDT.csv", "BNBUSDT", 1600756200, 1746218400);
  globalTrendAnalyzer.addPair("BNBUSDT",
                              "../rez/BNB/Original/2perc/BNBUSDTADXLog.csv");
  double BNBCashAvailable = 0.0;
  std::string BNBValueLog = "../rez/BNB/Original/2perc/BNBValueLog.csv";

  Agent agentDOGELong = Agent(
      1, 0.02, 10, 0.15, "../rez/DOGE/Original/2perc/DOGEUSDTLongSellLog.csv",
      "../rez/DOGE/Original/2perc/DOGEUSDTLongBuyLog.csv");
  Agent agentDOGEShort = Agent(
      -1, 0.02, 10, 0.15, "../rez/DOGE/Original/2perc/DOGEUSDTShortSellLog.csv",
      "../rez/DOGE/Original/2perc/DOGEUSDTShortBuyLog.csv");
  std::vector<Price> priceListDOGE =
      dp.getPrices("../data/DOGEUSDT.csv", "DOGEUSDT", 1600756200, 1746218400);
  globalTrendAnalyzer.addPair("DOGEUSDT",
                              "../rez/DOGE/Original/2perc/DOGEUSDTADXLog.csv");
  double DOGECashAvailable = 0.0;
  std::string DOGEValueLog = "../rez/DOGE/Original/2perc/DOGEValueLog.csv";

  Agent agentAVAXLong = Agent(
      1, 0.02, 10, 0.15, "../rez/AVAX/Original/2perc/AVAXUSDTLongSellLog.csv",
      "../rez/AVAX/Original/2perc/AVAXUSDTLongBuyLog.csv");
  Agent agentAVAXShort = Agent(
      -1, 0.02, 10, 0.15, "../rez/AVAX/Original/2perc/AVAXUSDTShortSellLog.csv",
      "../rez/AVAX/Original/2perc/AVAXUSDTShortBuyLog.csv");
  std::vector<Price> priceListAVAX =
      dp.getPrices("../data/AVAXUSDT.csv", "AVAXUSDT", 1600756200, 1746218400);
  globalTrendAnalyzer.addPair("AVAXUSDT",
                              "../rez/AVAX/Original/2perc/AVAXUSDTADXLog.csv");
  double AVAXCashAvailable = 0.0;
  std::string AVAXValueLog = "../rez/AVAX/Original/2perc/AVAXValueLog.csv";

  double globalFraction = 1.0;

  std::fstream fout;

  for (int i = 0; i < priceListBTC.size(); ++i) {
    // BTC
    // globalTrendAnalyzer.addPrice("BTCUSDT", priceListBTC [ i ]);
    BTCCashAvailable =
        agentBTCLong.run(priceListBTC [ i ], globalFraction, BTCCashAvailable);
    BTCCashAvailable =
        agentBTCShort.run(priceListBTC [ i ], globalFraction, BTCCashAvailable);
    fout.open(BTCValueLog, std::ios::out | std::ios::app);
    fout << priceListBTC [ i ].time << "," << BTCCashAvailable << ","
         << agentBTCLong.getInventoryValue(priceListBTC [ i ]) << ","
         << agentBTCShort.getInventoryValue(priceListBTC [ i ]) << "\r\n";
    fout.close();

    // ETH
    if (i < priceListETH.size()) {
      // globalTrendAnalyzer.addPrice("ETHUSDT", priceListETH [ i ]);
      ETHCashAvailable = agentETHLong.run(priceListETH [ i ], globalFraction,
                                          ETHCashAvailable);
      ETHCashAvailable = agentETHShort.run(priceListETH [ i ], globalFraction,
                                           ETHCashAvailable);
      fout.open(ETHValueLog, std::ios::out | std::ios::app);
      fout << priceListETH [ i ].time << "," << ETHCashAvailable << ","
           << agentETHLong.getInventoryValue(priceListETH [ i ]) << ","
           << agentETHShort.getInventoryValue(priceListETH [ i ]) << "\r\n";
      fout.close();
    }

    // SOL
    if (i < priceListSOL.size()) {
      // globalTrendAnalyzer.addPrice("SOLUSDT", priceListSOL [ i ]);
      SOLCashAvailable = agentSOLLong.run(priceListSOL [ i ], globalFraction,
                                          SOLCashAvailable);
      SOLCashAvailable = agentSOLShort.run(priceListSOL [ i ], globalFraction,
                                           SOLCashAvailable);
      fout.open(SOLValueLog, std::ios::out | std::ios::app);
      fout << priceListSOL [ i ].time << "," << SOLCashAvailable << ","
           << agentSOLLong.getInventoryValue(priceListSOL [ i ]) << ","
           << agentSOLShort.getInventoryValue(priceListSOL [ i ]) << "\r\n";
      fout.close();
    }

    // XRP
    if (i < priceListXRP.size()) {
      // globalTrendAnalyzer.addPrice("XRPUSDT", priceListXRP [ i ]);
      XRPCashAvailable = agentXRPLong.run(priceListXRP [ i ], globalFraction,
                                          XRPCashAvailable);
      XRPCashAvailable = agentXRPShort.run(priceListXRP [ i ], globalFraction,
                                           XRPCashAvailable);
      fout.open(XRPValueLog, std::ios::out | std::ios::app);
      fout << priceListXRP [ i ].time << "," << XRPCashAvailable << ","
           << agentXRPLong.getInventoryValue(priceListXRP [ i ]) << ","
           << agentXRPShort.getInventoryValue(priceListXRP [ i ]) << "\r\n";
      fout.close();
    }

    // ADA
    if (i < priceListADA.size()) {
      // globalTrendAnalyzer.addPrice("ADAUSDT", priceListADA [ i ]);
      ADACashAvailable = agentADALong.run(priceListADA [ i ], globalFraction,
                                          ADACashAvailable);
      ADACashAvailable = agentADAShort.run(priceListADA [ i ], globalFraction,
                                           ADACashAvailable);
      fout.open(ADAValueLog, std::ios::out | std::ios::app);
      fout << priceListADA [ i ].time << "," << ADACashAvailable << ","
           << agentADALong.getInventoryValue(priceListADA [ i ]) << ","
           << agentADAShort.getInventoryValue(priceListADA [ i ]) << "\r\n";
      fout.close();
    }

    // BNB
    if (i < priceListBNB.size()) {
      // globalTrendAnalyzer.addPrice("BNBUSDT", priceListBNB [ i ]);
      BNBCashAvailable = agentBNBLong.run(priceListBNB [ i ], globalFraction,
                                          BNBCashAvailable);
      BNBCashAvailable = agentBNBShort.run(priceListBNB [ i ], globalFraction,
                                           BNBCashAvailable);
      fout.open(BNBValueLog, std::ios::out | std::ios::app);
      fout << priceListBNB [ i ].time << "," << BNBCashAvailable << ","
           << agentBNBLong.getInventoryValue(priceListBNB [ i ]) << ","
           << agentBNBShort.getInventoryValue(priceListBNB [ i ]) << "\r\n";
      fout.close();
    }

    // DOGE
    if (i < priceListDOGE.size()) {
      // globalTrendAnalyzer.addPrice("DOGEUSDT", priceListDOGE [ i ]);
      DOGECashAvailable = agentDOGELong.run(priceListDOGE [ i ], globalFraction,
                                            DOGECashAvailable);
      DOGECashAvailable = agentDOGEShort.run(priceListDOGE [ i ],
                                             globalFraction, DOGECashAvailable);
      fout.open(DOGEValueLog, std::ios::out | std::ios::app);
      fout << priceListDOGE [ i ].time << "," << DOGECashAvailable << ","
           << agentDOGELong.getInventoryValue(priceListDOGE [ i ]) << ","
           << agentDOGEShort.getInventoryValue(priceListDOGE [ i ]) << "\r\n";
      fout.close();
    }

    // AVAX
    if (i < priceListAVAX.size()) {
      // globalTrendAnalyzer.addPrice("AVAXUSDT", priceListAVAX [ i ]);
      AVAXCashAvailable = agentAVAXLong.run(priceListAVAX [ i ], globalFraction,
                                            AVAXCashAvailable);
      AVAXCashAvailable = agentAVAXShort.run(priceListAVAX [ i ],
                                             globalFraction, AVAXCashAvailable);
      fout.open(AVAXValueLog, std::ios::out | std::ios::app);
      fout << priceListAVAX [ i ].time << "," << AVAXCashAvailable << ","
           << agentAVAXLong.getInventoryValue(priceListAVAX [ i ]) << ","
           << agentAVAXShort.getInventoryValue(priceListAVAX [ i ]) << "\r\n";
      fout.close();
    }

    // globalFraction = globalTrendAnalyzer.getBuyFraction();
    //  std::cout << "Buy fraction: " << globalFraction << std::endl;
  }

  return 0;
}
