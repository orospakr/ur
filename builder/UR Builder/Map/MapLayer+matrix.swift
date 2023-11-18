//
//  MapLayer+matrix.swift
//  UR Builder
//
//  Created by Andrew Clunis on 2023-11-16.
//

import Foundation

extension MapLayer {
    /// Return the tiletype index for a given tile coordinate. Width is the stride, in row major-order.
    func getTileAt(width: Int, x: Int, y: Int) -> Int {
        let index = (y * width) + x
        return Int(self.tiles[index])
    }
    
    /// Set the given tile to a given tiletype index. Width is the stride, in row major-order.
    mutating func setTileAt(width: Int, x: Int, y: Int, tileTypeIndex: Int) {
        let index = (y * width) + x
        self.tiles[index] = Int32(tileTypeIndex)
    }
}
