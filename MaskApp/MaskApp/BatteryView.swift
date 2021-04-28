//
//  BatteryView.swift
//  MaskApp
//
//  Created by David Nikiforov on 3/30/21.
//

import SwiftUI

struct BatteryView: View {
    @ObservedObject var bleManager: BLEManager
    var body: some View {
        NavigationView{
            ZStack {
                Color("BatteryBackground")
                    .edgesIgnoringSafeArea(.all)
                VStack {
                    Text("Battery Percentage")
                        .foregroundColor(Color("BatteryPercentageText"))
                        .font(Font.custom("Helvetica-Neue", size: 20))
                        .bold()
                        .frame(maxWidth: .infinity, maxHeight: 55, alignment: .center)
                        .offset(y: -80)
                    Spacer()
                    ZStack {
                        
                        Circle()
                            .frame(width: 190, height: 190)
                            .foregroundColor(Color("InnerCircle"))
                            .shadow(color: Color("BatteryShadow"), radius: 80, x: 0, y: 0) 
                        
                        let percentage = Double(bleManager.percentageVal.description)!/100
                        
                        Circle()
                            .trim(from: 0, to: CGFloat(percentage))
                            .stroke(Color("CircleLeft"), lineWidth: 7)
                            .frame(width: 260, height: 260)
                            .shadow(color: Color("CircleLeftShadow"), radius: 6, x: 0, y: 0)
                        
                        Circle()
                            .trim(from: CGFloat(percentage), to: 1)
                            .stroke(Color("CircleNotLeft"), lineWidth: 7)
                            .frame(width: 260, height: 260)
                        
                        Text(bleManager.percentageVal.description + "%")
                            .foregroundColor(Color("PercentageNumber"))
                            .font(Font.custom("Helvetica-Neue", size: 60))
                            .bold()
                    }
                    .offset(y: -80)
                    
                    Spacer()
                    HStack {
                        Spacer()
                        ZStack {
                            Rectangle()
                                .frame(width:130, height: 100)
                                .foregroundColor(Color("BoxColor"))
                                .cornerRadius(10)
                                .shadow(color: Color("BatteryShadow"), radius: 5, x: 0, y: 0)
                            
                            Text("Capacity (V)")
                                .font(Font.custom("Helvetica-Neue", size: 20))
                                .foregroundColor(Color("BoxText"))
                                .bold()
                                .offset(y: -30)
                            
                            Text("11.5V")
                                .font(Font.custom("Helvetica-Neue", size: 35))
                                .foregroundColor(Color("BoxText"))
                                .bold()
                                .offset(y: 15)
                        }
                        Spacer()
                        ZStack {
                            Rectangle()
                                .frame(width:130, height: 100)
                                .foregroundColor(Color("BoxColor"))
                                .cornerRadius(10)
                                .shadow(color: Color("BatteryShadow"), radius: 5, x: 0, y: 0)
                            
                            Text("Actual (V)")
                                .font(Font.custom("Helvetica-Neue", size: 20))
                                .foregroundColor(Color("BoxText"))
                                .bold()
                                .offset(y: -30)
                            
                            Text(bleManager.rawVoltage.description + "V")
                                .font(Font.custom("Helvetica-Neue", size: 35))
                                .bold()
                                .offset(y: 15)
                                .foregroundColor(Color("9VColor"))
                        }
                        Spacer()
                    }
                    .offset(y: -30)
                    Spacer()
                }
            }
        }
    }
}

struct BatteryView_Previews: PreviewProvider {
    static var previews: some View {
        BatteryView(bleManager: BLEManager())
            .preferredColorScheme(.dark)
            
            
            
    }
}
