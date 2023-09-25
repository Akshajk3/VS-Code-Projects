//
//  ContentView.swift
//  Test
//
//  Created by Akshaj Kanumuri on 9/24/23.
//

import SwiftUI

struct MeetingView: View {
    var body: some View {
        VStack {
            ProgressView(value: 5, total: 15)
            HStack {
                VStack {
                    Text("Seconds Elapsed")
                    Label("300", systemImage: <#T##String#>)
                }
                VStack {
                    Text("Seconds Remaining")
                }
            }
        }
    }
}

struct MeetingView_Previews: PreviewProvider {
    static var previews: some View {
        MeetingView()
    }
}
