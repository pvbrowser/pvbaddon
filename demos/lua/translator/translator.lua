-- translate helper functions
language_translator = rllib.rlIniFile()

function setLanguage(language)
  return language_translator.setDefaultSection(language_translator,language)
end

function readLanguageFile(filename)
  return language_translator.read(language_translator,filename)
end

function tr(text)
  return language_translator.i18n(language_translator,text,"tr_error:" .. text)
end
