import { Atmos } from "../atmos";

type StoredShader = Atmos.Asset.Script | null;

let vertex: StoredShader = null;
let fragment: StoredShader = null;

const retrieveShader = (existentShader: StoredShader, name: string) =>
    existentShader === null ? Atmos.Reliquary.send(Atmos.Traits.Asset.FindByName.Shader.typeName, { name: name }) : null;

export const main = (vertexShaderName: string, fragmentShaderName: string): Atmos.Result => {
    const material = Atmos.Reliquary.find(Atmos.Traits.Render.Raster.ExecutingMaterial.typeName)!;
    
    vertex = retrieveShader(vertex, vertexShaderName);
    fragment = retrieveShader(fragment, fragmentShaderName);

    const shaders = {
        vertex,
        fragment
    };

    Atmos.Reliquary.send(
        Atmos.Traits.Render.Raster.RecordCommands.typeName,
        {
            commands: [
                ...material.images.map(x => ({ shaders, ...x })),
                ...material.lines.map(x => ({ shaders, ...x })),
                ...material.regions.map(x => ({ shaders, ...x })),
                ...material.texts.map(x => ({ shaders, ...x }))
            ]
        });

    return {
        done: false
    };
};