const std = @import("std");
const sdl = @import("SDL2");
const protobuf = @import("protobuf");

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const sdl_sdk = sdl.init(b, .{ .dep_name = "SDL2" });

    const root_module = b.createModule(.{
        .root_source_file = b.path("src/main.zig"),
        .target = target,
        .optimize = optimize,
    });

    const exe = b.addExecutable(.{
        .name = "ur",
        .root_module = root_module,
    });

    exe.linkSystemLibrary("SDL2_image");
    exe.linkSystemLibrary("openmpt");
    exe.linkSystemLibrary("iconv");
    exe.linkFramework("Cocoa");
    exe.linkFramework("CoreAudio");
    exe.linkFramework("Carbon");
    exe.linkFramework("Metal");
    exe.linkFramework("QuartzCore");
    exe.linkFramework("AudioToolbox");
    exe.linkFramework("ForceFeedback");
    exe.linkFramework("GameController");
    exe.linkFramework("CoreHaptics");

    root_module.addImport("sdl2", sdl_sdk.getNativeModule());

    const protobuf_dep = b.dependency("protobuf", .{
        .target = target,
        .optimize = optimize,
    });
    root_module.addImport("protobuf", protobuf_dep.module("protobuf"));

    const gen_proto = b.step("gen-proto", "Generate zig files from .proto definitions");
    const protoc_step = protobuf.RunProtocStep.create(protobuf_dep.builder, target, .{
        .destination_directory = b.path("src/proto"),
        .source_files = &.{
            "proto/agm.proto",
        },
        .include_directories = &.{
            "proto",
        },
    });
    gen_proto.dependOn(&protoc_step.step);

    b.installArtifact(exe);

    const test_module = b.createModule(.{
        .root_source_file = b.path("src/tests.zig"),
        .target = target,
        .optimize = optimize,
    });
    test_module.addImport("protobuf", protobuf_dep.module("protobuf"));

    const unit_tests = b.addTest(.{
        .root_module = test_module,
    });

    const run_tests = b.addRunArtifact(unit_tests);
    const test_step = b.step("test", "Run unit tests");
    test_step.dependOn(&run_tests.step);
}
