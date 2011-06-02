import video

# decorator that lets the script engine know that the method is coroutine
def coroutine(func):
    return (True, func)

active_scripts = {}
pending_removal = []
pending_adds = []

# Extract a callable function from script, even if the function is actually a coroutine style generator
def extract_script_func(script, func):
    maybe_coroutine = getattr(script, func, None)
    if isinstance(maybe_coroutine, tuple):
        it = maybe_coroutine[1](script)
        return getattr(it, "next")
    else:
        return maybe_coroutine

def call_script_index(index):
    for script, functions in active_scripts.iteritems():
        func = functions[index]
        if func:
            try:
                func()
            except (StopIteration):
                remove_script(script)

def draw():
    call_script_index(0)

def init():
    video.add_draw_hook(draw)


def add_script(script):
    pending_adds.append(script)

def remove_script(script):
    pending_removal.append(script)


def do_frame():
    for script in pending_adds:
        draw_func = extract_script_func(script, "draw")
        do_frame_func = extract_script_func(script, "do_frame")
        finalize_func = extract_script_func(script, "finalize")

        active_scripts[script] = (draw_func, do_frame_func, finalize_func)

    del pending_adds[:]

    call_script_index(1)
    
    for script in pending_removal:
        finalize_func = getattr(script, "finalize", None)
        if finalize_func:
            finalize_func()
        del active_scripts[script]

    del pending_removal[:]


