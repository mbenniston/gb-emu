import { useGBEmu } from "@/context/GBEmuContext.tsx";
import { useEmulator } from "@/context/EmulatorContext.tsx";
import { useQuery } from "@tanstack/react-query";

type InstructionInfo = {
  opcode: number;
  mnemonic: string;
  isPrefix: boolean;
};

export function useInstructions() {
  const { module } = useGBEmu();
  const { emulator } = useEmulator();

  return useQuery({
    queryKey: ["instructions"],
    staleTime: Infinity,
    queryFn: () => {
      const instructionsTables = emulator.get_debug_instruction_table();

      const instructions_table_array = new Array<InstructionInfo>(
        instructionsTables.instructions_length,
      );
      for (let i = 0; i < instructionsTables.instructions_length; i++) {
        const gbInstruction = instructionsTables.get_instructions(i);

        instructions_table_array[i] = {
          opcode: gbInstruction.opcode,
          isPrefix: gbInstruction.isPrefix,
          mnemonic: gbInstruction.mnemonic,
        };
      }

      const extended_instructions_table_array = new Array<InstructionInfo>(
        instructionsTables.extended_instructions_length,
      );
      for (
        let i = 0;
        i < instructionsTables.extended_instructions_length;
        i++
      ) {
        const gbInstruction = instructionsTables.get_extended_instructions(i);
        extended_instructions_table_array[i] = {
          opcode: gbInstruction.opcode,
          isPrefix: gbInstruction.isPrefix,
          mnemonic: gbInstruction.mnemonic,
        };
      }

      module.destroy(instructionsTables);

      return {
        instructions: instructions_table_array,
        prefixed_instructions: extended_instructions_table_array,
      };
    },
  });
}
