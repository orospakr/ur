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
                .toolbar(content: {
                    Button("Import classic folder…") {
                        // show file picker:
                        let panel = NSOpenPanel()
                        panel.canChooseDirectories = true

                        panel.begin { result in
                            if result == .OK {
                                guard let url = panel.url else {
                                    return
                                }

                                // check if layerA.agm is present in the directory:
                                let layerAUrl = url.appendingPathComponent("layerA.agm")
                                guard FileManager.default.fileExists(atPath: layerAUrl.path) else {
                                    // display a dialog saying that this isn't a UR level folder
                                    let alert = NSAlert()
                                    alert.messageText = "This folder doesn't appear to be a UR level folder."
                                    alert.informativeText = "The file layerA.agm was not found in the selected folder."
                                    alert.runModal()
                                    return
                                }

                                do {
                                    try file.document.state = AGM.loadLegacyCSVFormat(directory: url)
                                } catch {
                                    let alert = NSAlert()
                                    alert.messageText = "Unable to import classic UR AGM format"
                                    alert.informativeText = error.localizedDescription
                                    alert.runModal()
                                    return
                                }
                                
                                
                                
                            }
                        }

                    }
                })
        }
        // TODO: lol commandgroup can't see document, so using toolbar instead
    }
}
