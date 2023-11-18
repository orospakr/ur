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
            mapLayer.uuid = UUID().uuidString
            mapLayer.tiles = (0..<(100 * 100)).map { _ in Int32(0) }
            mapLayer.width = 100
            mapLayer.height = 100
            return mapLayer
        }
        return agm
    }
}

extension TileType {
    // these "stock" tiletypes inherited from the map can have static assigned UUIDs
    
    static var grass: TileType {
        var type = TileType()
        type.title = "Grass"
        type.graphicIndex = 0
        type.solid = false
        type.uuid = "92EA39EF-6628-40AA-A7CE-7F4DB9052985"
        return type
    }

    static var trees1: TileType {
        var type = TileType()
        type.title = "Trees 1"
        type.graphicIndex = 1
        type.solid = true
        type.uuid = "787D9D99-26C5-467C-A6DF-ACA7F5C6116D"
        return type
    }

    static var boulder: TileType {
        var type = TileType()
        type.title = "Boulder"
        type.graphicIndex = 2
        type.solid = true
        type.uuid = "AB54A4B2-7651-4426-A053-90CBD4544E05"
        return type
    }

    static var water: TileType {
        var type = TileType()
        type.title = "Water"
        type.graphicIndex = 3
        type.solid = true
        type.uuid = "731690DB-EFA4-4470-A69D-70496DC85447"
        return type
    }

    static var void: TileType {
        var type = TileType()
        type.title = "Void"
        type.graphicIndex = 4
        type.solid = true
        type.uuid = "20EE1E3C-2208-4013-9AA3-2A33DDC24CEA"
        return type
    }

    static var gazeboRoof: TileType {
        var type = TileType()
        type.title = "Gazebo Roof"
        type.graphicIndex = 5
        type.solid = true
        type.uuid = "3ECE8B44-910B-428C-8A25-86FBEC63FFBA"
        return type
    }

    static var gazeboPillar: TileType {
        var type = TileType()
        type.title = "Gazebo Pillar"
        type.graphicIndex = 6
        type.solid = true
        type.uuid = "1101667D-1F27-4272-883B-3642E24553E8"
        return type
    }

    static var trees2: TileType {
        var type = TileType()
        type.title = "Trees 2"
        type.graphicIndex = 7
        type.solid = true
        type.uuid = "571A30DD-1370-4028-8DCD-F7C7FA9B560B"
        return type
    }

    static var trees3: TileType {
        var type = TileType()
        type.title = "Trees 3"
        type.graphicIndex = 8
        type.solid = true
        type.uuid = "745A15A4-FA43-4030-BE7A-C786E9A5BFE9"
        return type
    }

    static var trees4: TileType {
        var type = TileType()
        type.title = "Trees 4"
        type.graphicIndex = 9
        type.solid = true
        type.uuid = "81251115-87EB-4A1C-B5E0-1CD406B46E97"
        return type
    }

    static var trees5: TileType {
        var type = TileType()
        type.title = "Trees 5"
        type.graphicIndex = 10
        type.solid = true
        type.uuid = "67D05367-2593-4E24-A06A-A36227555FBB"
        return type
    }

    static var trees6: TileType {
        var type = TileType()
        type.title = "Trees 6"
        type.graphicIndex = 11
        type.solid = true
        type.uuid = "F0E4080E-D284-4A7D-9390-7BDA604E4A0E"
        return type
    }

    static var trees7: TileType {
        var type = TileType()
        type.title = "Trees 7"
        type.graphicIndex = 12
        type.solid = true
        type.uuid = "A09173D7-1AC4-46EB-82B3-C35C412C9064"
        return type
    }

    static var trees8: TileType {
        var type = TileType()
        type.title = "Trees 8"
        type.graphicIndex = 13
        type.solid = true
        type.uuid = "A49A3F0E-9415-4C48-B678-C3E05C802CE9"
        return type
    }

    static var trees9: TileType {
        var type = TileType()
        type.title = "Trees 9"
        type.graphicIndex = 14
        type.solid = true
        type.uuid = "56F9AA96-857D-4A23-B204-99376176936D"
        return type
    }
}
