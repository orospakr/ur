//
//  Explorer.swift
//  UR Builder
//
//  Created by Andrew Clunis on 2023-11-18.
//

import Foundation
import SwiftUI

struct ExplorerView: View {
    var tileset: Tileset
    @ObservedObject var editorState: EditorState
    
    @Binding var tileTypes: [TileType]
    @Binding var layers: [MapLayer]
    
    var body: some View {
        TabView {
            tileTypeExplorer.tabItem { Text("Tiles") }
            layerExplorer.tabItem { Text("Layers") }
        }
    }
    
    var tileTypeExplorer: some View {
        List {
            ForEach(Array(tileTypes.enumerated()), id: \.offset) { _, tileType in
                HStack {
                    Image(nsImage: tileset.tiles[Int(tileType.graphicIndex)].previewImage)
                    Text(tileType.title)
                }
            }
        }
    }
    
    var layerExplorer: some View {
        List {
            ForEach(Array(layers.enumerated()), id: \.offset) { idx, layer in
                HStack {
                    Toggle(isOn: Binding<Bool>.init(get: {
                        return !editorState.disabledLayers.contains(idx)
                    }, set: { enabled in
                        if (enabled) {
                            editorState.disabledLayers.remove(idx)
                        } else {
                            editorState.disabledLayers.insert(idx)
                        }
                    })) {
                        Text("Layer \(idx + 1)")
                    }
                }
            }
        }
    }
}

extension TileType: Identifiable {
    var id: String {
        // TODO: this won't work once renable
        self.title
    }
}

extension MapLayer: Identifiable {
    var id: String {
        self.uuid
    }
}
