//
//  UR_BuilderApp.swift
//  UR Builder
//
//  Created by Andrew Clunis on 2023-11-15.
//

import SwiftUI

@main
struct UR_BuilderApp: App {
    var body: some Scene {
        DocumentGroup(newDocument: URMapDocument()) { file in
            ContentView(document: file.$document)
        }
    }
}
