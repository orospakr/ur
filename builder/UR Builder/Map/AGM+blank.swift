//
//  AGM+blank.swift
//  UR Builder
//
//  Created by Andrew Clunis on 2023-11-17.
//

import Foundation

extension AGM {
    static var blank: AGM {
        var agm = AGM()
        agm.tileTypes = [
            .grass,
            .trees1,
            .boulder,
            .water,
            .void,
            .gazeboRoof,
            .gazeboPillar,
            .trees2,
            .trees3,
            .trees4,
            .trees5,
            .trees6,
            .trees7,
            .trees8,
            .trees9,
        ]
        agm.width = 100
        agm.height = 100
        agm.title = "Greenfield"
        agm.layers = (0..<3).map { index in
            var mapLayer = MapLayer()
            mapLayer.tiles = (0..<(100 * 100)).map { _ in Int32(0) }
            return mapLayer
        }
        return agm
    }
}

extension TileType {
    static var grass: TileType {
        var type = TileType()
        type.title = "Grass"
        type.graphicIndex = 0
        type.solid = false
        return type
    }

    static var trees1: TileType {
        var type = TileType()
        type.title = "Trees 1"
        type.graphicIndex = 1
        type.solid = true
        return type
    }

    static var boulder: TileType {
        var type = TileType()
        type.title = "Boulder"
        type.graphicIndex = 2
        type.solid = true
        return type
    }

    static var water: TileType {
        var type = TileType()
        type.title = "Water"
        type.graphicIndex = 3
        type.solid = true
        return type
    }

    static var void: TileType {
        var type = TileType()
        type.title = "Void"
        type.graphicIndex = 4
        type.solid = true
        return type
    }

    static var gazeboRoof: TileType {
        var type = TileType()
        type.title = "Gazebo Roof"
        type.graphicIndex = 5
        type.solid = true
        return type
    }

    static var gazeboPillar: TileType {
        var type = TileType()
        type.title = "Gazebo Pillar"
        type.graphicIndex = 6
        type.solid = true
        return type
    }

    static var trees2: TileType {
        var type = TileType()
        type.title = "Trees 2"
        type.graphicIndex = 7
        type.solid = true
        return type
    }

    static var trees3: TileType {
        var type = TileType()
        type.title = "Trees 3"
        type.graphicIndex = 8
        type.solid = true
        return type
    }

    static var trees4: TileType {
        var type = TileType()
        type.title = "Trees 4"
        type.graphicIndex = 9
        type.solid = true
        return type
    }

    static var trees5: TileType {
        var type = TileType()
        type.title = "Trees 5"
        type.graphicIndex = 10
        type.solid = true
        return type
    }

    static var trees6: TileType {
        var type = TileType()
        type.title = "Trees 6"
        type.graphicIndex = 11
        type.solid = true
        return type
    }

    static var trees7: TileType {
        var type = TileType()
        type.title = "Trees 7"
        type.graphicIndex = 12
        type.solid = true
        return type
    }

    static var trees8: TileType {
        var type = TileType()
        type.title = "Trees 8"
        type.graphicIndex = 13
        type.solid = true
        return type
    }

    static var trees9: TileType {
        var type = TileType()
        type.title = "Trees 9"
        type.graphicIndex = 14
        type.solid = true
        return type
    }
}
