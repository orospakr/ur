//
//  CanvasView.swift
//  UR Builder
//
//  Created by Andrew Clunis on 2023-11-18.
//

import Foundation
import SwiftUI
import os.log


struct CanvasView: View {
    let tileTypes: [TileType]
    let mapSize: AGM.MapSize
    @ObservedObject var editorState: EditorState
    
    let tileset: Tileset
    
    @Binding var mapLayers: [MapLayer]
    
    private let scaleFactor = 1
    
    private let tileSize = 32
    
    @State private var reticleLocation: (Int, Int)? = nil
    
    var body: some View {
        ZStack {
            ForEach(Array(mapLayers.enumerated()), id: \.offset) { layerIdx, mapLayer in
                if !editorState.disabledLayers.contains(layerIdx) {
                    Canvas { context, size in
                        (0..<mapSize.width).forEach { x in
                            (0..<mapSize.height).forEach { y in
                                let tileIndex = mapLayer.getTileAt(width: mapSize.width, x: x, y: y)
                                                
                                context.draw(Image(tileset.tiles[tileIndex].firstFrame, scale: 1.0, label: Text("tile")), in: CGRect.init(origin: .init(x: x * tileSize * scaleFactor, y: y * tileSize * scaleFactor), size: CGSize(width: tileSize * scaleFactor, height: tileSize * scaleFactor)), style: FillStyle(eoFill: false, antialiased: false))
                            }
                        }
                    }.opacity(editorState.activeLayer == layerIdx ? 1.0 : 0.5)
                }
            }
            Canvas { context, size in
                if let reticleLocation = self.reticleLocation {
                    context.stroke(Path(CGRect(x: tileSize * reticleLocation.0, y: tileSize * reticleLocation.1, width: tileSize, height: tileSize)), with: .color(.red), lineWidth: 2)
                }
            }
            
        }
        .frame(width: CGFloat(mapSize.width * tileSize), height: CGFloat(mapSize.height * tileSize))
        .onContinuousHover(coordinateSpace: .local) { hoverPhase in
            switch(hoverPhase) {
            case .active(let location):
                reticleLocation = (Int(location.x) / tileSize, Int(location.y) / tileSize)
            case .ended:
                reticleLocation = nil
            }
        }.onTapGesture(count: 1, coordinateSpace: .local) { point in
            guard let activeLayerIdx = editorState.activeLayer, let activeTileType = editorState.activeTileType else {
                return
            }
            let xCoord: Int = Int(point.x) / tileSize
            let yCoord: Int = Int(point.y) / tileSize
            // this mutates (and copies) the entire layer, but that's OK for now.
            mapLayers[activeLayerIdx].setTileAt(width: mapSize.width, x: xCoord, y: yCoord, tileTypeIndex: activeTileType)
        }
    }
}
