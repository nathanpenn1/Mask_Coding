//
//  GraphView.swift
//  MaskApp
//
//  Created by David Nikiforov on 3/30/21.
//

import SwiftUI
import SwiftUICharts

struct GraphView: View {
    @ObservedObject var bleManager: BLEManager
    var body: some View {
        NavigationView {
            ZStack {
                Color("BatteryBackground")
                    .edgesIgnoringSafeArea(.all)
                HStack() {
                    LineView(data: bleManager.yVal , title: "UV Intesity", legend: "(nm)")
                        .background(Color("BatteryBackground"))
                }
            }
        }
    }
}

struct GraphView_Previews: PreviewProvider {
    static var previews: some View {
        GraphView(bleManager: BLEManager())
            .preferredColorScheme(.light)
    }
}
