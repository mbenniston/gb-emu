export function getAddressLabel(address: number) {
  if (address < 0x4000) {
    // ROM bank 0
    return "ROM0";
  }
  if (address < 0x8000) {
    return "ROMN";
  }
  if (address < 0xa000) {
    return "VRAM";
  }
  if (address < 0xc000) {
    return "ERAM";
  }
  if (address < 0xe000) {
    return "WRAM";
  }
  if (address < 0xfe00) {
    return "ECHO";
  }
  if (address < 0xfea0) {
    return "OAM";
  }
  if (address < 0xff00) {
    return "-";
  }
  if (address < 0xff80) {
    return "IO";
  }

  if (address < 0xffff) {
    return "HRAM";
  }

  if (address === 0xffff) {
    return "IR";
  }

  return "UKWN";
}
