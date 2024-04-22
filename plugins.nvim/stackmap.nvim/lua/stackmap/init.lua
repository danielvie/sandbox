local M = {}

-- M.setup = function(opts)
--     print("Options: ", opts)
-- end

local find_mapping = function(maps, lhs)
    for _, value in ipairs(maps) do
        if value.lhs == lhs then
            return value
        end

        print(value.lhs)
        if string.find(string.lower(value.lhs), "<space>") then
            print(value.lhs)
            print(lhs)
            break
        end
    end
end

local s = "daniel"

if string.find(s, "dniel") then
    print('asdfasdfasdf')
end


M.push = function(name, mode, mappings)
    print("aqui: " .. mode)
    local maps = vim.api.nvim_get_keymap(mode)

    P(find_mapping(maps, "<Space>s"))
    -- P(maps)
end

M.pop = function(name)

end

M.push("debug_mode", "n", {
    ["<leader>st"] = "echo 'Hello'",
    ["<leader>sz"] = "echo 'Goodbye'",
})

return M
