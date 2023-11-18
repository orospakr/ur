//
//  Tileset.swift
//  UR Builder
//
//  Created by Andrew Clunis on 2023-11-16.
//

import Foundation
import AppKit
import CoreGraphics

///
class Tileset {
    var tiles: [AnimatedTile] = []

    init() {
        // define type for tile in the tileset, then TODO with all its animation frames
        
        // grab tiles.png out of bundle
        guard let tiles = Bundle.main.image(forResource: "tiles") else {
            assertionFailure("can't load tile set")
            tiles = []
            return
        }
        
        // cgimage:
        guard let tileCgimage = tiles.cgImage(forProposedRect: nil, context: nil, hints: nil) else {
            assertionFailure("Could not coerce tiles NSimage to CGImage")
            self.tiles = []
            return
        }
        
        let tileSize = 32
        
        // number of tile types in this image?
        let numTiles: Int = Int(tiles.size.width) / tileSize
        let animFrames: Int = Int(tiles.size.height) / tileSize // (should be 8)

        self.tiles = (0..<numTiles).map { tileIndex in
            let tileX = tileIndex * tileSize
            let tileRect = CGRect(x: tileX, y: 0, width: tileSize, height: tileSize * animFrames)
            let tileImage = tiles.cgImage(forProposedRect: nil, context: nil, hints: nil)?.cropping(to: tileRect)
            
            // for each tile, make an AnimatedTile
            let frames = (0..<animFrames).map { frameIndex in
                let frameY = frameIndex * tileSize
                let frameRect = CGRect(x: 0, y: frameY, width: tileSize, height: tileSize)
                return tileImage!.cropping(to: frameRect)!
            }
            
            return AnimatedTile(frames: frames)
        }
    }
}

/// A tile in the tileset.
class AnimatedTile {
    let frames: [CGImage]
    
    let previewImage: NSImage

    init(frames: [CGImage]) {
        self.frames = frames
        self.previewImage = NSImage(cgImage: frames.first!, size: NSSize(width: frames.first!.width, height: frames.first!.height))
    }
    
    var firstFrame: CGImage {
        self.frames.first!
    }
}
