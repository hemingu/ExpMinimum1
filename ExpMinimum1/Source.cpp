#include "Common.h"

#include "ADCInfo.h"
#include "Const.h"


using namespace Constants;



int main(int argc, char *argv[])
{
    // Open ROOT window
    TApplication app("Root Window", &argc, argv);


    // file input (Files in same location as Source.cpp)
    // (Y:\Documents\Visual Studio 2017\Projects\ConsoleApplication1\ConsoleApplication1)
    TFile *fileCo = new TFile("AH2017Jun07_120130.root", "read");
    TFile *fileCs = new TFile("AH2017Jun07_121525.root", "read");
    TFile *fileBa = new TFile("AH2017Jun07_122129.root", "read");
    TFile *fileBG = new TFile("AH2017Jun07_122616.root", "read");
    //TFile *fileHist = new TFile("histgrams.root", "read");


    // Make Co60 Class
    ADCInfo infoCo(fileCo, Element::Co);
    TH1D *histCo = new TH1D("ADC Co60", Constants::AXIS_NAME, Constants::BIN, Constants::HISTMIN, Constants::HISTMAX);
    for (Int_t i = 0; i < infoCo.nEntries; i++)
    {
        histCo->Fill((Double_t)infoCo.ADCChannel[i]);
    }
    TCanvas *c1 = new TCanvas();
    histCo->Draw();

    // Cs137
    ADCInfo infoCs(fileCs, Element::Cs);
    TH1D *histCs = new TH1D("ADC Cs137", Constants::AXIS_NAME, Constants::BIN, Constants::HISTMIN, Constants::HISTMAX);
    for (Int_t i = 0; i < infoCs.nEntries; i++)
    {
        histCs->Fill((Double_t)infoCs.ADCChannel[i]);
    }
    //TCanvas *c2 = new TCanvas();
    //histCs->Draw();

    // Ba133
    ADCInfo infoBa(fileCs, Element::Ba);
    TH1D *histBa = new TH1D("ADC Ba133", AXIS_NAME, BIN, HISTMIN, HISTMAX);
    for (Int_t i = 0; i < infoBa.nEntries; i++)
    {
        histBa->Fill((Double_t)infoBa.ADCChannel[i]);
    }
    //TCanvas *c3 = new TCanvas();
    //histBa->Draw();

    // BackGround
    ADCInfo infoBG(fileBG, Element::BG);
    TH1D *histBG = new TH1D("ADC BG", AXIS_NAME, BIN, HISTMIN, HISTMAX);
    for (Int_t i = 0; i < infoBG.nEntries; i++)
    {
        histBG->Fill((Double_t)infoBG.ADCChannel[i]);
    }
    TCanvas *c4 = new TCanvas();
    histBG->Draw();

    TH1D *histCoBG = new TH1D("ADC Co60 - BG", AXIS_NAME, BIN, HISTMIN, HISTMAX);
    histCoBG->Add(histCo, histBG, 1.0, -(Double_t)infoCo.measurementTime / (Double_t)infoBG.measurementTime);
    //histCoBG->Scale(1.0 / (infoBG.measurementTime + infoCo.measurementTime));
    TCanvas *c5 = new TCanvas();
    histCoBG->Draw();


    app.Run();

    return 0;

}