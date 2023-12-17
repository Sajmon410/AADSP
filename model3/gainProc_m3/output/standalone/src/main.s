	.public _enable
	.public _inputGain
	.public _inverter
	.public _limiterThreshold
	.public _mode
	.public _sampleBuffer
	.public _variablesGain
	.extern _audio_invert_init
	.extern _cl_wavread_bits_per_sample
	.extern _cl_wavread_close
	.extern _cl_wavread_frame_rate
	.extern _cl_wavread_getnchannels
	.extern _cl_wavread_number_of_frames
	.extern _cl_wavread_open
	.extern _cl_wavread_recvsample
	.extern _cl_wavwrite_close
	.extern _cl_wavwrite_open
	.extern _cl_wavwrite_sendsample
	.extern _gainProcessing
	.public _main
	.extern _printf
	.extern _strcpy
	.extern __div
	.xdata_ovly
__extractedConst_0_1
	.dw  (0x26666666)
	.xdata_ovly
__extractedConst_1_1
	.dw  (0x73333333)
	.xdata_ovly
__extractedConst_2_1
	.dw  (0x5a9e1b09)
	.xdata_ovly
_enable
	.dw  (0x1)
	.xdata_ovly
_inputGain
	.dw  (0x8020c49c)
	.xdata_ovly
_inverter
	.dw  (0x26666666)
	.dw  (0x73333333)
	.xdata_ovly
_limiterThreshold
	.dw  (0x7fdf3b64)
	.xdata_ovly
_mode
	.dw  (0x0)
	.ydata_ovly
_sampleBuffer
	.bss (0x80)
	.xdata_ovly
_string_const_0
	.dw  (0x45)
	.dw  (0x72)
	.dw  (0x72)
	.dw  (0x6f)
	.dw  (0x72)
	.dw  (0x3a)
	.dw  (0x20)
	.dw  (0x43)
	.dw  (0x6f)
	.dw  (0x75)
	.dw  (0x6c)
	.dw  (0x64)
	.dw  (0x20)
	.dw  (0x6e)
	.dw  (0x6f)
	.dw  (0x74)
	.dw  (0x20)
	.dw  (0x6f)
	.dw  (0x70)
	.dw  (0x65)
	.dw  (0x6e)
	.dw  (0x20)
	.dw  (0x77)
	.dw  (0x61)
	.dw  (0x76)
	.dw  (0x65)
	.dw  (0x66)
	.dw  (0x69)
	.dw  (0x6c)
	.dw  (0x65)
	.dw  (0x2e)
	.dw  (0xa)
	.dw  (0x0)
	.xdata_ovly
_string_const_1
	.dw  (0x45)
	.dw  (0x72)
	.dw  (0x72)
	.dw  (0x6f)
	.dw  (0x72)
	.dw  (0x3a)
	.dw  (0x20)
	.dw  (0x43)
	.dw  (0x6f)
	.dw  (0x75)
	.dw  (0x6c)
	.dw  (0x64)
	.dw  (0x20)
	.dw  (0x6e)
	.dw  (0x6f)
	.dw  (0x74)
	.dw  (0x20)
	.dw  (0x6f)
	.dw  (0x70)
	.dw  (0x65)
	.dw  (0x6e)
	.dw  (0x20)
	.dw  (0x77)
	.dw  (0x61)
	.dw  (0x76)
	.dw  (0x65)
	.dw  (0x66)
	.dw  (0x69)
	.dw  (0x6c)
	.dw  (0x65)
	.dw  (0x2e)
	.dw  (0xa)
	.dw  (0x0)
	.xdata_ovly
_variablesGain
	.bss (0x2)
	.code_ovly



	# This construction should ensure linking of crt0 in case when target is a standalone program without the OS
	.if defined(_OVLY_)
		.if .strcmp('standalone',_OVLY_)=0
		.if .strcmp('crystal32',_TARGET_FAMILY_)=0
			.extern __start         # dummy use of __start to force linkage of crt0
dummy		.equ(__start)
		.else
			.extern __intvec         # dummy use of __intvec to force linkage of intvec
dummy		.equ(__intvec)
		.endif
		.endif
	.endif

_main:			/* LN: 115 | CYCLE: 0 | RULES: () */ 
	xmem[i7] = i7			# LN: 115 | 
	i7 += 1			# LN: 115 | 
	i7 = i7 + (0x20f)			# LN: 115 | 
	i1 = i7 - (0x1)			# LN: 115 | 
	xmem[i1] = a0h			# LN: 115 | 
	i1 = i7 - (0x2)			# LN: 115 | 
	xmem[i1] = i0			# LN: 115 | 
cline_115_0:			/* LN: 131 | CYCLE: 0 | RULES: () */ 
	a0 = xmem[__extractedConst_0_1 + 0]			# LN: 131 | 
	a1 = xmem[__extractedConst_1_1 + 0]			# LN: 131 | 
	i0 = (0) + (_inverter)			# LN: 131 | 
	call (_audio_invert_init)			# LN: 131 | 
cline_131_0:			/* LN: 133 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x3)			# LN: 133 | 
	a0 = 0			# LN: 133 | 
	xmem[i0] = a0h			# LN: 133 | 
	do (0x8), label_end_93			# LN: 133 | 
cline_133_0:			/* LN: 134 | CYCLE: 0 | RULES: () */ 
label_begin_93:			/* LN: 133 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x4)			# LN: 134 | 
	a0 = 0			# LN: 134 | 
	xmem[i0] = a0h			# LN: 134 | 
	do (0x10), label_end_92			# LN: 134 | 
cline_134_0:			/* LN: 135 | CYCLE: 0 | RULES: () */ 
label_begin_92:			/* LN: 134 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x3)			# LN: 135 | 
	a0 = xmem[i0]; a1 = 0			# LN: 135, 135 | 
	a0 = a0 << 4			# LN: 135 | 
	i0 = a0			# LN: 135 | 
	i1 = i7 - (0x4)			# LN: 135 | 
	i0 = i0 + (_sampleBuffer + 0)			# LN: 135 | 
	a0 = xmem[i1]			# LN: 135 | 
	b0 = i0			# LN: 135 | 
	a0 = a0 + b0			# LN: 135 | 
	AnyReg(i0, a0h)			# LN: 135 | 
	nop #empty cycle
	ymem[i0] = a1h			# LN: 135 | 
cline_135_0:			/* LN: 134 | CYCLE: 0 | RULES: () */ 
init_latch_label_0:			/* LN: 135 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x4)			# LN: 134 | 
	a0 = xmem[i0]			# LN: 134 | 
	uhalfword(a1) = (0x1)			# LN: 134 | 
	a0 = a0 + a1			# LN: 134 | 
	i0 = i7 - (0x4)			# LN: 134 | 
label_end_92:			# LN: 134 | CYCLE: 5 | RULES: ()
	xmem[i0] = a0h			# LN: 134 | 
cline_134_1:			/* LN: 133 | CYCLE: 0 | RULES: () */ 
init_latch_label_1:			/* LN: 135 | CYCLE: 0 | RULES: () */ 
for_end_1:			/* LN: 134 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x3)			# LN: 133 | 
	a0 = xmem[i0]			# LN: 133 | 
	uhalfword(a1) = (0x1)			# LN: 133 | 
	a0 = a0 + a1			# LN: 133 | 
	i0 = i7 - (0x3)			# LN: 133 | 
label_end_93:			# LN: 133 | CYCLE: 5 | RULES: ()
	xmem[i0] = a0h			# LN: 133 | 
cline_133_1:			/* LN: 139 | CYCLE: 0 | RULES: () */ 
for_end_0:			/* LN: 133 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x2)			# LN: 139 | 
	i0 = xmem[i0]			# LN: 139 | 
	i1 = i7 - (260 - 0)			# LN: 139 | 
	i4 = xmem[i0]			# LN: 139 | 
	i0 = i1			# LN: 139 | 
	i1 = i4			# LN: 139 | 
	call (_strcpy)			# LN: 139 | 
cline_139_0:			/* LN: 140 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (260 - 0)			# LN: 140 | 
	call (_cl_wavread_open)			# LN: 140 | 
	AnyReg(i0, a0h)			# LN: 140 | 
	i1 = i7 - (0x105)			# LN: 140 | 
	xmem[i1] = i0			# LN: 140 | 
cline_140_0:			/* LN: 141 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x105)			# LN: 141 | 
	a0 = xmem[i0]			# LN: 141 | 
	a0 & a0			# LN: 141 | 
	if (a != 0) jmp (else_0)			# LN: 141 | 
cline_141_0:			/* LN: 143 | CYCLE: 0 | RULES: () */ 
	i0 = (0) + (_string_const_0)			# LN: 143 | 
	call (_printf)			# LN: 143 | 
cline_143_0:			/* LN: 144 | CYCLE: 0 | RULES: () */ 
	halfword(a0) = (0xffff)			# LN: 144 | 
	jmp (__epilogue_242)			# LN: 144 | 
cline_144_0:			/* LN: 147 | CYCLE: 0 | RULES: () */ 
endif_0:			/* LN: 141 | CYCLE: 0 | RULES: () */ 
else_0:			/* LN: 141 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x1)			# LN: 147 | 
	a0 = xmem[i0]			# LN: 147 | 
	uhalfword(a1) = (0x3)			# LN: 147 | 
	a0 - a1			# LN: 147 | 
	if (a < 0) jmp (else_1)			# LN: 147 | 
cline_147_0:			/* LN: 148 | CYCLE: 0 | RULES: () */ 
	uhalfword(a0) = (0x1)			# LN: 148 | 
	xmem[_enable + 0] = a0h			# LN: 148 | 
cline_148_0:			/* LN: 149 | CYCLE: 0 | RULES: () */ 
	a0 = xmem[__extractedConst_2_1 + 0]			# LN: 149 | 
	xmem[_inputGain + 0] = a0h			# LN: 149 | 
cline_149_0:			/* LN: 150 | CYCLE: 0 | RULES: () */ 
	a0 = 0			# LN: 150 | 
	xmem[_mode + 0] = a0h			# LN: 150 | 
	jmp (endif_1)			# LN: 150 | 
cline_150_0:			/* LN: 154 | CYCLE: 0 | RULES: () */ 
endif_1:			/* LN: 147 | CYCLE: 0 | RULES: () */ 
else_1:			/* LN: 147 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x105)			# LN: 154 | 
	i0 = xmem[i0]			# LN: 154 | 
	call (_cl_wavread_getnchannels)			# LN: 154 | 
	i0 = i7 - (0x106)			# LN: 154 | 
	xmem[i0] = a0h			# LN: 154 | 
cline_154_0:			/* LN: 155 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x105)			# LN: 155 | 
	i0 = xmem[i0]			# LN: 155 | 
	call (_cl_wavread_bits_per_sample)			# LN: 155 | 
	i0 = i7 - (0x107)			# LN: 155 | 
	xmem[i0] = a0h			# LN: 155 | 
cline_155_0:			/* LN: 156 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x105)			# LN: 156 | 
	i0 = xmem[i0]			# LN: 156 | 
	call (_cl_wavread_frame_rate)			# LN: 156 | 
	i0 = i7 - (0x108)			# LN: 156 | 
	xmem[i0] = a0h			# LN: 156 | 
cline_156_0:			/* LN: 157 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x105)			# LN: 157 | 
	i0 = xmem[i0]			# LN: 157 | 
	call (_cl_wavread_number_of_frames)			# LN: 157 | 
	i0 = i7 - (0x109)			# LN: 157 | 
	xmem[i0] = a0h			# LN: 157 | 
cline_157_0:			/* LN: 162 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x2)			# LN: 162 | 
	i0 = xmem[i0]			# LN: 162 | 
	i1 = i7 - (521 - 0)			# LN: 162 | 
	i0 += 1			# LN: 162 | 
	i4 = xmem[i0]			# LN: 162 | 
	i0 = i1			# LN: 162 | 
	i1 = i4			# LN: 162 | 
	call (_strcpy)			# LN: 162 | 
cline_162_0:			/* LN: 163 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20a)			# LN: 163 | 
	uhalfword(a0) = (0x4)			# LN: 163 | 
	xmem[i0] = a0h			# LN: 163 | 
cline_163_0:			/* LN: 164 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (521 - 0)			# LN: 164 | 
	i1 = i7 - (0x107)			# LN: 164 | 
	a0 = xmem[i1]			# LN: 164 | 
	i1 = i7 - (0x20a)			# LN: 164 | 
	a1 = xmem[i1]			# LN: 164 | 
	i1 = i7 - (0x108)			# LN: 164 | 
	b0 = xmem[i1]			# LN: 164 | 
	call (_cl_wavwrite_open)			# LN: 164 | 
	AnyReg(i0, a0h)			# LN: 164 | 
	i1 = i7 - (0x20b)			# LN: 164 | 
	xmem[i1] = i0			# LN: 164 | 
cline_164_0:			/* LN: 165 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20b)			# LN: 165 | 
	a0 = xmem[i0]			# LN: 165 | 
	a0 & a0			# LN: 165 | 
	if (a != 0) jmp (else_2)			# LN: 165 | 
cline_165_0:			/* LN: 167 | CYCLE: 0 | RULES: () */ 
	i0 = (0) + (_string_const_1)			# LN: 167 | 
	call (_printf)			# LN: 167 | 
cline_167_0:			/* LN: 168 | CYCLE: 0 | RULES: () */ 
	halfword(a0) = (0xffff)			# LN: 168 | 
	jmp (__epilogue_242)			# LN: 168 | 
cline_168_0:			/* LN: 181 | CYCLE: 0 | RULES: () */ 
endif_2:			/* LN: 165 | CYCLE: 0 | RULES: () */ 
else_2:			/* LN: 165 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20c)			# LN: 181 | 
	a0 = 0			# LN: 181 | 
	xmem[i0] = a0h			# LN: 181 | 
for_2:			/* LN: 181 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x109)			# LN: 181 | 
	a0 = xmem[i0]			# LN: 181 | 
	uhalfword(a1) = (0x10)			# LN: 181 | 
	call (__div)			# LN: 181 | 
	i0 = i7 - (0x20c)			# LN: 181 | 
	a1 = xmem[i0]			# LN: 181 | 
	a1 - a0			# LN: 181 | 
	if (a >= 0) jmp (for_end_2)			# LN: 181 | 
cline_181_0:			/* LN: 183 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20d)			# LN: 183 | 
	a0 = 0			# LN: 183 | 
	xmem[i0] = a0h			# LN: 183 | 
	do (0x10), label_end_94			# LN: 183 | 
cline_183_0:			/* LN: 185 | CYCLE: 0 | RULES: () */ 
label_begin_94:			/* LN: 183 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20e)			# LN: 185 | 
	a0 = 0			# LN: 185 | 
	xmem[i0] = a0h			# LN: 185 | 
for_4:			/* LN: 185 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20e)			# LN: 185 | 
	a0 = xmem[i0]			# LN: 185 | 
	i0 = i7 - (0x106)			# LN: 185 | 
	a1 = xmem[i0]			# LN: 185 | 
	a0 - a1			# LN: 185 | 
	if (a >= 0) jmp (for_end_4)			# LN: 185 | 
cline_185_0:			/* LN: 187 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x105)			# LN: 187 | 
	i0 = xmem[i0]			# LN: 187 | 
	call (_cl_wavread_recvsample)			# LN: 187 | 
	i0 = i7 - (0x20f)			# LN: 187 | 
	xmem[i0] = a0h			# LN: 187 | 
cline_187_0:			/* LN: 188 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20e)			# LN: 188 | 
	a0 = xmem[i0]			# LN: 188 | 
	a0 = a0 << 4			# LN: 188 | 
	i0 = a0			# LN: 188 | 
	i1 = i7 - (0x20d)			# LN: 188 | 
	i0 = i0 + (_sampleBuffer + 0)			# LN: 188 | 
	a0 = xmem[i1]			# LN: 188 | 
	a1 = i0			# LN: 188 | 
	a0 = a1 + a0			# LN: 188 | 
	AnyReg(i0, a0h)			# LN: 188 | 
	i1 = i7 - (0x20f)			# LN: 188 | 
	a0 = xmem[i1]			# LN: 188 | 
	ymem[i0] = a0h			# LN: 188 | 
cline_188_0:			/* LN: 185 | CYCLE: 0 | RULES: () */ 
init_latch_label_2:			/* LN: 189 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20e)			# LN: 185 | 
	a0 = xmem[i0]			# LN: 185 | 
	uhalfword(a1) = (0x1)			# LN: 185 | 
	a0 = a0 + a1			# LN: 185 | 
	i0 = i7 - (0x20e)			# LN: 185 | 
	xmem[i0] = a0h			# LN: 185 | 
	jmp (for_4)			# LN: 185 | 
cline_185_1:			/* LN: 183 | CYCLE: 0 | RULES: () */ 
init_latch_label_3:			/* LN: 190 | CYCLE: 0 | RULES: () */ 
for_end_4:			/* LN: 185 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20d)			# LN: 183 | 
	a0 = xmem[i0]			# LN: 183 | 
	uhalfword(a1) = (0x1)			# LN: 183 | 
	a0 = a0 + a1			# LN: 183 | 
	i0 = i7 - (0x20d)			# LN: 183 | 
label_end_94:			# LN: 183 | CYCLE: 5 | RULES: ()
	xmem[i0] = a0h			# LN: 183 | 
cline_183_1:			/* LN: 192 | CYCLE: 0 | RULES: () */ 
for_end_3:			/* LN: 183 | CYCLE: 0 | RULES: () */ 
	a0 = xmem[_enable + 0]			# LN: 192 | 
	uhalfword(a1) = (0x1)			# LN: 192 | 
	a0 - a1			# LN: 192 | 
	if (a != 0) jmp (else_3)			# LN: 192 | 
	i0 = (0) + (_sampleBuffer)			# LN: 192 | 
	i1 = (0) + (_sampleBuffer)			# LN: 192 | 
	call (_gainProcessing)			# LN: 192 | 
	jmp (endif_3)			# LN: 192 | 
cline_192_0:			/* LN: 194 | CYCLE: 0 | RULES: () */ 
endif_3:			/* LN: 192 | CYCLE: 0 | RULES: () */ 
else_3:			/* LN: 192 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20d)			# LN: 194 | 
	a0 = 0			# LN: 194 | 
	xmem[i0] = a0h			# LN: 194 | 
	do (0x10), label_end_95			# LN: 194 | 
cline_194_0:			/* LN: 196 | CYCLE: 0 | RULES: () */ 
label_begin_95:			/* LN: 194 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20e)			# LN: 196 | 
	a0 = 0			# LN: 196 | 
	xmem[i0] = a0h			# LN: 196 | 
for_6:			/* LN: 196 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20e)			# LN: 196 | 
	a0 = xmem[i0]			# LN: 196 | 
	i0 = i7 - (0x20a)			# LN: 196 | 
	a1 = xmem[i0]			# LN: 196 | 
	a0 - a1			# LN: 196 | 
	if (a >= 0) jmp (for_end_6)			# LN: 196 | 
cline_196_0:			/* LN: 198 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20e)			# LN: 198 | 
	a0 = xmem[i0]			# LN: 198 | 
	a0 = a0 << 4			# LN: 198 | 
	i0 = a0			# LN: 198 | 
	i1 = i7 - (0x20d)			# LN: 198 | 
	i0 = i0 + (_sampleBuffer + 0)			# LN: 198 | 
	a0 = xmem[i1]			# LN: 198 | 
	a1 = i0			# LN: 198 | 
	a0 = a1 + a0			# LN: 198 | 
	AnyReg(i0, a0h)			# LN: 198 | 
	i1 = i7 - (0x20f)			# LN: 198 | 
	a0 = ymem[i0]			# LN: 198 | 
	xmem[i1] = a0h			# LN: 198 | 
cline_198_0:			/* LN: 199 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20b)			# LN: 199 | 
	i1 = i7 - (0x20f)			# LN: 199 | 
	a0 = xmem[i1]			# LN: 199 | 
	i0 = xmem[i0]			# LN: 199 | 
	call (_cl_wavwrite_sendsample)			# LN: 199 | 
cline_199_0:			/* LN: 196 | CYCLE: 0 | RULES: () */ 
init_latch_label_4:			/* LN: 200 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20e)			# LN: 196 | 
	a0 = xmem[i0]			# LN: 196 | 
	uhalfword(a1) = (0x1)			# LN: 196 | 
	a0 = a0 + a1			# LN: 196 | 
	i0 = i7 - (0x20e)			# LN: 196 | 
	xmem[i0] = a0h			# LN: 196 | 
	jmp (for_6)			# LN: 196 | 
cline_196_1:			/* LN: 194 | CYCLE: 0 | RULES: () */ 
init_latch_label_5:			/* LN: 201 | CYCLE: 0 | RULES: () */ 
for_end_6:			/* LN: 196 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20d)			# LN: 194 | 
	a0 = xmem[i0]			# LN: 194 | 
	uhalfword(a1) = (0x1)			# LN: 194 | 
	a0 = a0 + a1			# LN: 194 | 
	i0 = i7 - (0x20d)			# LN: 194 | 
label_end_95:			# LN: 194 | CYCLE: 5 | RULES: ()
	xmem[i0] = a0h			# LN: 194 | 
cline_194_1:			/* LN: 181 | CYCLE: 0 | RULES: () */ 
init_latch_label_6:			/* LN: 202 | CYCLE: 0 | RULES: () */ 
for_end_5:			/* LN: 194 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20c)			# LN: 181 | 
	a0 = xmem[i0]			# LN: 181 | 
	uhalfword(a1) = (0x1)			# LN: 181 | 
	a0 = a0 + a1			# LN: 181 | 
	i0 = i7 - (0x20c)			# LN: 181 | 
	xmem[i0] = a0h			# LN: 181 | 
	jmp (for_2)			# LN: 181 | 
cline_181_1:			/* LN: 207 | CYCLE: 0 | RULES: () */ 
for_end_2:			/* LN: 181 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x105)			# LN: 207 | 
	i0 = xmem[i0]			# LN: 207 | 
	call (_cl_wavread_close)			# LN: 207 | 
cline_207_0:			/* LN: 208 | CYCLE: 0 | RULES: () */ 
	i0 = i7 - (0x20b)			# LN: 208 | 
	i0 = xmem[i0]			# LN: 208 | 
	call (_cl_wavwrite_close)			# LN: 208 | 
cline_208_0:			/* LN: 211 | CYCLE: 0 | RULES: () */ 
	a0 = 0			# LN: 211 | 
	jmp (__epilogue_242)			# LN: 211 | 
cline_211_0:			/* LN: 212 | CYCLE: 0 | RULES: () */ 
__epilogue_242:			/* LN: 212 | CYCLE: 0 | RULES: () */ 
	i7 = i7 - (0x20f)			# LN: 212 | 
	i7 -= 1			# LN: 212 | 
	ret			# LN: 212 | 
