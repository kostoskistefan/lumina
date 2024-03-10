#!/usr/bin/python

import os 
import math
import argparse
import numpy as np
from datetime import datetime
from PIL import Image, ImageDraw, ImageFont

def lfc_parse_arguments() -> dict:
    parser = argparse.ArgumentParser(description='Generate a new C project')

    parser.add_argument('--bpp', type=str, required=False, default='4', help='Defines how many bits per pixel to use for the generated font')
    parser.add_argument('--name', type=str, required=True, help='The name of the generated lumina compatible font')
    parser.add_argument('--font', type=str, required=True, help='The path to the font file to convert')
    parser.add_argument('--height', type=int, required=True, help='The height of the generated font')
    parser.add_argument('--ascii_range', type=str, required=True, help='A list of comma separated ASCII characters to convert. E.g. 65,66-70,75')

    arguments = parser.parse_args()

    return {
        'bpp': arguments.bpp,
        'font': arguments.font,
        'name': arguments.name,
        'height': arguments.height,
        'ascii_range': arguments.ascii_range,
    }

def lfc_expand_ascii_range(input_ascii_range: str) -> list:
    expanded_ranges = []

    for ascii_range in input_ascii_range.split(','):
        if '-' in ascii_range:
            ascii_range_start, ascii_range_end = ascii_range.split('-')
            expanded_ranges.extend(list(range(int(ascii_range_start), int(ascii_range_end) + 1)))
        else:
            expanded_ranges.append(int(ascii_range))

    expanded_ranges = sorted(expanded_ranges)

    # Remove characters that are not in the ASCII range and convert to character type
    expanded_ranges = list([chr(x) for x in expanded_ranges if x >= 0 and x <= 127])

    return expanded_ranges

def lfc_calculate_baseline_offset(font: ImageFont.truetype) -> int:
    surface = Image.new('L', (font_height * 15, font_height * 5), color=0)
    draw = ImageDraw.Draw(surface)

    # Draw the test string
    draw.text((0, 0), '"#$\'?@[_`jpy|', font=font, fill=255)

    return np.argmax(np.array(surface).any(axis=1))

def lfc_character_generate_data(character: str, baseline_offset: int, bpp: int, font: ImageFont.truetype) -> (np.array, int):
    # Create a surface to draw the character
    surface = Image.new('L', (font.size * 2, font.size * 2), color=0)
    draw = ImageDraw.Draw(surface)

    # Draw the character
    draw.text((0, -baseline_offset), character, font=font, fill=255)

    # Convert the surface to a numpy array
    surface = np.array(surface)

    # Remove zero columns
    surface = surface[:, surface.any(axis=0)]

    # Remove the trailing zero rows
    surface = surface[:np.max(np.where(np.any(surface != 0, axis=1))) + 1]

    untrimmed_height = surface.shape[0]

    # Remove all zero rows
    surface = surface[surface.any(axis=1)]

    y_offset = untrimmed_height - surface.shape[0]

    surface //= 2 ** (8 - bpp)

    return (surface, y_offset)

def lfc_character_data_to_bitmap(character_data: np.array, bpp: int) -> np.array:
    return np.array([f'{x:0{bpp}b}' for row in character_data for x in row], dtype=f'U{bpp}').reshape(character_data.shape)

def lfc_character_bitmap_pad(character_bitmap: np.array, bpp: int) -> np.array:
    row_length = len(character_bitmap[0])
    chunk_size = 8 // bpp 

    if row_length % chunk_size == 0:
        return character_bitmap 

    number_of_bits_per_row = (row_length * bpp)
    pad_length = ((((number_of_bits_per_row - 1) // 8 + 1) * 8) - number_of_bits_per_row) // bpp 
    pad_element = '0' * bpp

    return np.pad(character_bitmap, ((0, 0), (0, pad_length)), mode='constant', constant_values=pad_element)

def lfc_character_bitmap_to_c_glyph_bitmap(character_bitmap: np.array, bpp: int) -> np.array:
    c_glyph_bitmap = []

    for row in character_bitmap:
        joined_row = ''.join(row)
        binary_chunks = [joined_row[i:i + 8] for i in range(0, len(joined_row), 8)]
        hex_chunks = [f'0x{int(binary_chunk, 2):0>2x},' for binary_chunk in binary_chunks]
        c_glyph_bitmap.append(hex_chunks)

    return np.array(c_glyph_bitmap)

if __name__ == '__main__':
    arguments = lfc_parse_arguments()

    bpp = int(arguments['bpp'])
    
    if bpp not in [1, 2, 4, 8]:
        raise Exception('The bpp parameter must be 1, 2, 4, or 8')

    font_file = arguments['font']
    output_name = arguments['name']
    font_height = int(arguments['height'])
    ascii_range = arguments['ascii_range']

    font = ImageFont.truetype(font_file, font_height)

    character_list = lfc_expand_ascii_range(ascii_range)
    baseline_offset = lfc_calculate_baseline_offset(font)

    c_info = '#include "lumina_font.h"\n\n'
    c_info += '// ' + '-' * 120 + '\n'
    c_info += f'// Generated with lumina-font-converter.py\n'
    c_info += f'// Font name: {output_name}\n'
    c_info += f'// Font file: {os.path.basename(font_file)}\n'
    c_info += f'// Font height: {font_height}\n'
    c_info += f'// ASCII range: {ascii_range}\n'
    c_info += f'// Bits per pixel: {bpp}\n'
    c_info += f'// Generated on: {datetime.now().strftime("%Y-%m-%d %H:%M:%S")}\n'
    c_info += '// ' + '-' * 120 + '\n\n'

    c_font_data_array = f'const lumina_font_t {output_name} = {{\n'
    c_font_data_array += f"\t.bpp = {bpp},\n"
    c_font_data_array += f"\t.glyph_data = {output_name}_glyph_data,\n"
    c_font_data_array += f"\t.glyph_bitmap = {output_name}_glyph_bitmap,\n"
    c_font_data_array += f"\t.glyph_data_index = {output_name}_glyph_data_index,\n"
    c_font_data_array += "};\n"

    c_glyph_bitmap_array = f'static const uint8_t {output_name}_glyph_bitmap[] = {{\n'
    c_glyph_data_array = f'static const lumina_font_glyph_data_t {output_name}_glyph_data[] = {{\n'
    c_glyph_data_array += f'\t{{ .width = 0, .length = 0, .y_offset = 0, .glyph_bitmap_index = 0 }}, // Reserved by Lumina\n'

    c_glyph_indices = f"static const uint8_t {output_name}_glyph_data_index[] = {{\n"

    byte_count = 0
    glyph_indices = [0] * 128

    for i in range(len(character_list)):
        character = character_list[i]
        (character_data, y_offset) = lfc_character_generate_data(character, baseline_offset, bpp, font)
        character_bitmap = lfc_character_data_to_bitmap(character_data, bpp)
        character_bitmap_padded = lfc_character_bitmap_pad(character_bitmap, bpp)

        width = character_bitmap.shape[1]
        c_glyph_bitmap = lfc_character_bitmap_to_c_glyph_bitmap(character_bitmap_padded, bpp)

        c_glyph_data_array += f'\t{{ .width = {width}, .length = {c_glyph_bitmap.size}, .y_offset = {y_offset}, .glyph_bitmap_index = {byte_count} }},\n'
        c_glyph_bitmap_array += f'\t// Character "{character}" (dec:{ord(character)}, hex:0x{ord(character):02x}), Width: {width}, Y-Offset: {y_offset}\n'
        c_glyph_bitmap_array += ''.join(['\t' + ' '.join(row) + '\n' for row in c_glyph_bitmap])

        if i < len(character_list) - 1:
            c_glyph_bitmap_array += '\n'

        byte_count += c_glyph_bitmap.size
        glyph_indices[ord(character)] = i + 1

    c_glyph_indices += '\n'.join([f"\t{str(glyph_indices[i])+',':<4} // Character ascii code: {str(i)}" for i in range(len(glyph_indices))])
    c_glyph_indices += "\n};\n\n"
    c_glyph_bitmap_array += '};\n\n'
    c_glyph_data_array += '};\n\n'

    if not os.path.exists('generated'):
        os.makedirs('generated')

    with open(f'generated/{output_name}.c', 'w') as output_file:
        output_file.write(c_info)
        output_file.write(c_glyph_bitmap_array)
        output_file.write(c_glyph_data_array)
        output_file.write(c_glyph_indices)
        output_file.write(c_font_data_array)
